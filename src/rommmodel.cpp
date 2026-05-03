#include "rommmodel.h"
#include "rommclient.h"
#include "rommcovercache.h"

RommModel::RommModel(QObject *parent)
    : QAbstractListModel(parent)
{
}

void RommModel::setClient(RommClient *client)
{
    m_client = client;
    connect(client, &RommClient::platformsFetched, this, &RommModel::onPlatformsFetched);
    connect(client, &RommClient::romsFetched, this, [this](const QVariantList &items, int total) {
        onRomsFetched(items, total, m_currentPage);
    });
    connect(client, &RommClient::busyChanged, this, [this]() {
        setBusy(m_client->busy());
    });
    connect(client, &RommClient::statusTextChanged, this, [this]() {
        setStatusText(m_client->statusText());
    });
    connect(client, &RommClient::error, this, &RommModel::error);
}

void RommModel::setCoverCache(RommCoverCache *cache)
{
    m_coverCache = cache;
}

int RommModel::rowCount(const QModelIndex &) const
{
    return m_entries.size();
}

QVariant RommModel::data(const QModelIndex &index, int role) const
{
    if (index.row() < 0 || index.row() >= m_entries.size())
        return {};
    const auto &e = m_entries[index.row()];
    switch (role) {
    case RomIdRole:
        return e.id;
    case NameRole:
        return e.name;
    case FileNameRole:
        return e.fileNames.isEmpty() ? QString{} : e.fileNames.first();
    case FileNamesRole:
        return e.fileNames;
    case PlatformIdRole:
        return e.platformId;
    case PlatformSlugRole:
        return e.platformSlug;
    case CoverUrlRole:
        return e.coverUrl;
    case LocalCoverRole:
        return e.localCover;
    case FileSizeBytesRole:
        return e.fileSizeBytes;
    }
    return {};
}

QHash<int, QByteArray> RommModel::roleNames() const
{
    return {
        {RomIdRole, "romId"},
        {NameRole, "name"},
        {FileNameRole, "fileName"},
        {FileNamesRole, "fileNames"},
        {PlatformIdRole, "platformId"},
        {PlatformSlugRole, "platformSlug"},
        {CoverUrlRole, "coverUrl"},
        {LocalCoverRole, "localCover"},
        {FileSizeBytesRole, "fileSizeBytes"},
    };
}

bool RommModel::busy() const
{
    return m_busy;
}

QString RommModel::statusText() const
{
    return m_statusText;
}

void RommModel::setBusy(bool b)
{
    if (m_busy == b)
        return;
    m_busy = b;
    Q_EMIT busyChanged();
}

void RommModel::setStatusText(const QString &s)
{
    if (m_statusText == s)
        return;
    m_statusText = s;
    Q_EMIT statusTextChanged();
}

void RommModel::fetchPlatforms()
{
    if (m_client)
        m_client->fetchPlatforms();
}

void RommModel::fetchRoms(int platformId, const QString &search, int page)
{
    if (!m_client)
        return;
    m_currentPage = page;
    m_client->fetchRoms(platformId, search, page);
}

QVariantMap RommModel::getRom(int index) const
{
    if (index < 0 || index >= m_entries.size())
        return {};
    const auto &e = m_entries[index];
    QVariantMap m;
    m[QStringLiteral("romId")] = e.id;
    m[QStringLiteral("name")] = e.name;
    m[QStringLiteral("fileName")] = e.fileNames.isEmpty() ? QString{} : e.fileNames.first();
    m[QStringLiteral("fileNames")] = e.fileNames;
    m[QStringLiteral("platformId")] = e.platformId;
    m[QStringLiteral("platformSlug")] = e.platformSlug;
    m[QStringLiteral("coverUrl")] = e.coverUrl;
    m[QStringLiteral("localCover")] = e.localCover;
    m[QStringLiteral("fileSizeBytes")] = e.fileSizeBytes;
    return m;
}

void RommModel::notifyCoverCached(int romId, const QString &localPath)
{
    for (int i = 0; i < m_entries.size(); ++i) {
        if (m_entries[i].id == romId) {
            m_entries[i].localCover = localPath;
            auto idx = createIndex(i, 0);
            Q_EMIT dataChanged(idx, idx, {LocalCoverRole});
            return;
        }
    }
}

void RommModel::onPlatformsFetched(const QVariantList &platforms)
{
    Q_EMIT platformsFetched(platforms);
}

void RommModel::onRomsFetched(const QVariantList &items, int total, int page)
{
    m_total = total;

    if (page == 1) {
        beginResetModel();
        m_entries.clear();
        for (const auto &var : items) {
            auto map = var.toMap();
            RomEntry e;
            e.id = map[QStringLiteral("id")].toInt();
            e.name = map[QStringLiteral("name")].toString();
            e.fileNames = map[QStringLiteral("fileNames")].toStringList();
            e.platformId = map[QStringLiteral("platformId")].toInt();
            e.platformSlug = map[QStringLiteral("platformSlug")].toString();
            e.coverUrl = map[QStringLiteral("coverUrl")].toString();
            e.fileSizeBytes = map[QStringLiteral("fileSizeBytes")].toLongLong();
            // Check cover cache
            if (m_coverCache)
                e.localCover = m_coverCache->cachedPath(e.id);
            m_entries.append(e);
        }
        endResetModel();
        Q_EMIT countChanged();
    } else {
        // Append page
        int first = m_entries.size();
        int last = first + items.size() - 1;
        if (last < first) {
            Q_EMIT romsFetched(false);
            return;
        }
        beginInsertRows({}, first, last);
        for (const auto &var : items) {
            auto map = var.toMap();
            RomEntry e;
            e.id = map[QStringLiteral("id")].toInt();
            e.name = map[QStringLiteral("name")].toString();
            e.fileNames = map[QStringLiteral("fileNames")].toStringList();
            e.platformId = map[QStringLiteral("platformId")].toInt();
            e.platformSlug = map[QStringLiteral("platformSlug")].toString();
            e.coverUrl = map[QStringLiteral("coverUrl")].toString();
            e.fileSizeBytes = map[QStringLiteral("fileSizeBytes")].toLongLong();
            if (m_coverCache)
                e.localCover = m_coverCache->cachedPath(e.id);
            m_entries.append(e);
        }
        endInsertRows();
        Q_EMIT countChanged();
    }

    // Request covers for entries without one
    if (m_coverCache) {
        for (const auto &e : std::as_const(m_entries)) {
            if (e.localCover.isEmpty() && !e.coverUrl.isEmpty())
                m_coverCache->requestCover(e.id, e.coverUrl);
        }
    }

    Q_EMIT romsFetched(m_entries.size() < m_total);
}
