#pragma once

#include <QObject>
#include <QVariantList>

class WineScanner : public QObject
{
    Q_OBJECT

public:
    explicit WineScanner(QObject *parent = nullptr);

    Q_INVOKABLE QVariantList findWineVersions() const;
    Q_INVOKABLE QString localWinePath() const;
    Q_INVOKABLE QString homePath() const;
};
