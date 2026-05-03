#include "rommfiledownloader.h"
#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QUrl>

RommFileDownloader::RommFileDownloader(QObject *parent)
    : Downloader(parent)
{
}

void RommFileDownloader::setApiKey(const QString &key)
{
    m_apiKey = key;
}

void RommFileDownloader::setRomCacheDir(const QString &dir)
{
    m_romCacheDir = dir;
}

void RommFileDownloader::setServerUrl(const QString &url)
{
    QString trimmed = url.trimmed();
    while (trimmed.endsWith(QLatin1Char('/')))
        trimmed.chop(1);
    m_serverUrl = trimmed;
}

static QString safeFileName(const QString &fileName)
{
    // Use only the basename in case ROMM includes a subdirectory in file_name
    return QFileInfo(fileName).fileName();
}

QString RommFileDownloader::cachedRomPath(int romId, const QString &fileName) const
{
    if (m_romCacheDir.isEmpty())
        return {};
    QString path = m_romCacheDir + QStringLiteral("/files/") + QString::number(romId) + QLatin1Char('/') + safeFileName(fileName);
    return QFileInfo::exists(path) ? path : QString();
}

void RommFileDownloader::downloadRom(int romId, const QString &fileName)
{
    if (busy()) {
        Q_EMIT downloadError(romId, QStringLiteral("A download is already in progress"));
        return;
    }

    QString cached = cachedRomPath(romId, fileName);
    if (!cached.isEmpty()) {
        Q_EMIT romDownloaded(romId, cached);
        return;
    }

    if (m_serverUrl.isEmpty()) {
        Q_EMIT downloadError(romId, QStringLiteral("ROMM server URL not configured"));
        return;
    }

    if (m_romCacheDir.isEmpty()) {
        Q_EMIT downloadError(romId, QStringLiteral("ROM cache directory not configured"));
        return;
    }

    QString baseName = safeFileName(fileName);
    QString saveDir = m_romCacheDir + QStringLiteral("/files/") + QString::number(romId);
    if (!QDir().mkpath(saveDir)) {
        Q_EMIT downloadError(romId, QStringLiteral("Cannot create directory: %1").arg(saveDir));
        return;
    }
    QString savePath = saveDir + QLatin1Char('/') + baseName;

    QUrl url(m_serverUrl + QStringLiteral("/api/roms/") + QString::number(romId) + QStringLiteral("/content/")
             + QString::fromUtf8(QUrl::toPercentEncoding(fileName)));
    QNetworkRequest req(url);
    if (!m_apiKey.isEmpty())
        req.setRawHeader("Authorization", QByteArrayLiteral("Bearer ") + m_apiKey.toUtf8());
    req.setAttribute(QNetworkRequest::RedirectPolicyAttribute, QNetworkRequest::NoLessSafeRedirectPolicy);

    setBusy(true);
    setStatusText(QStringLiteral("Downloading %1…").arg(fileName));
    setProgress(0.0);

    auto *file = new QFile(savePath, this);
    if (!file->open(QIODevice::WriteOnly)) {
        setBusy(false);
        QString err = file->errorString();
        file->deleteLater();
        Q_EMIT downloadError(romId, QStringLiteral("Cannot write to %1: %2").arg(savePath, err));
        return;
    }

    auto *reply = nam().get(req);

    connect(reply, &QNetworkReply::downloadProgress, this, [this](qint64 received, qint64 total) {
        if (total > 0)
            setProgress(static_cast<double>(received) / total);
    });

    connect(reply, &QNetworkReply::readyRead, this, [reply, file]() {
        file->write(reply->readAll());
    });

    connect(reply, &QNetworkReply::finished, this, [this, reply, file, romId, savePath, fileName]() {
        reply->deleteLater();
        file->close();
        file->deleteLater();
        setBusy(false);

        if (reply->error() != QNetworkReply::NoError) {
            QFile::remove(savePath);
            Q_EMIT downloadError(romId, reply->errorString());
            return;
        }

        setStatusText(QStringLiteral("Downloaded %1").arg(fileName));
        setProgress(1.0);
        Q_EMIT romDownloaded(romId, savePath);
    });
}
