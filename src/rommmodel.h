#pragma once

#include <QAbstractListModel>
#include <QStringList>
#include <QVariantList>
#include <QVector>

class RommClient;
class RommCoverCache;

class RommModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(int count READ rowCount NOTIFY countChanged)
    Q_PROPERTY(bool busy READ busy NOTIFY busyChanged)
    Q_PROPERTY(QString statusText READ statusText NOTIFY statusTextChanged)

public:
    enum Roles {
        RomIdRole = Qt::UserRole + 1,
        NameRole,
        FileNameRole,
        FileNamesRole,
        PlatformIdRole,
        PlatformSlugRole,
        CoverUrlRole,
        LocalCoverRole,
        FileSizeBytesRole,
    };

    explicit RommModel(QObject *parent = nullptr);

    void setClient(RommClient *client);
    void setCoverCache(RommCoverCache *cache);

    int rowCount(const QModelIndex &parent = {}) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    QHash<int, QByteArray> roleNames() const override;

    bool busy() const;
    QString statusText() const;

    Q_INVOKABLE void fetchPlatforms();
    Q_INVOKABLE void fetchRoms(int platformId, const QString &search = {}, int page = 1);
    Q_INVOKABLE QVariantMap getRom(int index) const;

    void notifyCoverCached(int romId, const QString &localPath);

Q_SIGNALS:
    void countChanged();
    void busyChanged();
    void statusTextChanged();
    void platformsFetched(const QVariantList &platforms);
    void romsFetched(bool hasMore);
    void error(const QString &message);

private:
    struct RomEntry {
        int id = 0;
        QString name;
        QStringList fileNames;
        int platformId = 0;
        QString platformSlug;
        QString coverUrl;
        QString localCover;
        qint64 fileSizeBytes = 0;
    };

    void onPlatformsFetched(const QVariantList &platforms);
    void onRomsFetched(const QVariantList &items, int total, int page);
    void setBusy(bool b);
    void setStatusText(const QString &s);

    RommClient *m_client = nullptr;
    RommCoverCache *m_coverCache = nullptr;
    QVector<RomEntry> m_entries;
    int m_currentPage = 1;
    int m_total = 0;
    bool m_busy = false;
    QString m_statusText;
};
