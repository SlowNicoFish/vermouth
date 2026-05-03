#pragma once

#include "downloader.h"

class RommFileDownloader : public Downloader
{
    Q_OBJECT

public:
    explicit RommFileDownloader(QObject *parent = nullptr);

    void setApiKey(const QString &key);
    void setRomCacheDir(const QString &dir);
    void setServerUrl(const QString &url);

    Q_INVOKABLE void downloadRom(int romId, const QString &fileName);
    Q_INVOKABLE QString cachedRomPath(int romId, const QString &fileName) const;

Q_SIGNALS:
    void romDownloaded(int romId, const QString &localPath);
    void downloadError(int romId, const QString &message);

private:
    QString m_apiKey;
    QString m_romCacheDir;
    QString m_serverUrl;
};
