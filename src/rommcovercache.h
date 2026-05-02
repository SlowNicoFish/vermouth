#pragma once

#include <QHash>
#include <QNetworkAccessManager>
#include <QObject>
#include <QSet>

class RommCoverCache : public QObject
{
    Q_OBJECT

public:
    explicit RommCoverCache(QObject *parent = nullptr);

    void setCacheDir(const QString &dir);
    void setApiKey(const QString &key);

    // If already cached, emits coverReady synchronously.
    // If in-flight or URL empty, does nothing.
    void requestCover(int romId, const QString &coverUrl);

    QString cachedPath(int romId) const;

Q_SIGNALS:
    void coverReady(int romId, const QString &localPath);

private:
    QString buildLocalPath(int romId, const QString &url) const;
    void scanExisting();

    QNetworkAccessManager m_nam;
    QString m_cacheDir;
    QString m_apiKey;
    QSet<int> m_inFlight;
    QHash<int, QString> m_cache; // romId -> local file path
};
