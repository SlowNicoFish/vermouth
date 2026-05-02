#pragma once

#include "downloader.h"
#include <QVariantList>
#include <functional>

class QNetworkReply;

class RommClient : public Downloader
{
    Q_OBJECT
    Q_PROPERTY(QString serverUrl READ serverUrl WRITE setServerUrl NOTIFY serverUrlChanged)
    Q_PROPERTY(QString apiKey READ apiKey WRITE setApiKey NOTIFY apiKeyChanged)

public:
    explicit RommClient(QObject *parent = nullptr);

    QString serverUrl() const;
    void setServerUrl(const QString &url);
    QString apiKey() const;
    void setApiKey(const QString &key);

    Q_INVOKABLE void fetchPlatforms();
    Q_INVOKABLE void fetchRoms(int platformId, const QString &search = {}, int page = 1);

Q_SIGNALS:
    void serverUrlChanged();
    void apiKeyChanged();
    void platformsFetched(const QVariantList &platforms);
    void romsFetched(const QVariantList &items, int total);
    void error(const QString &message);

private:
    void makeRequest(const QUrl &url, std::function<void(const QByteArray &)> onData);
    QString resolveCoverUrl(const QJsonObject &romObj) const;

    QString m_serverUrl;
    QString m_apiKey;
    static constexpr int kPageSize = 500;
};
