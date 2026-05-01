#include "appentry.h"

QJsonObject AppEntry::toJson() const
{
    QJsonObject obj;
    obj[QStringLiteral("id")] = id;
    obj[QStringLiteral("name")] = name;
    obj[QStringLiteral("exePath")] = exePath;
    obj[QStringLiteral("runtimeType")] = runtimeType == Proton ? QStringLiteral("proton")
        : runtimeType == Wine                                  ? QStringLiteral("wine")
                                                               : QStringLiteral("native");
    obj[QStringLiteral("protonPath")] = protonPath;
    obj[QStringLiteral("protonPrefix")] = protonPrefix;
    obj[QStringLiteral("wineBinary")] = wineBinary;
    obj[QStringLiteral("winePrefix")] = winePrefix;
    obj[QStringLiteral("iconPath")] = iconPath;
    obj[QStringLiteral("gridPath")] = gridPath;
    obj[QStringLiteral("heroPath")] = heroPath;
    obj[QStringLiteral("logoPath")] = logoPath;
    obj[QStringLiteral("steamGridDbId")] = steamGridDbId;
    obj[QStringLiteral("launchOptions")] = launchOptions;
    obj[QStringLiteral("enableLogging")] = enableLogging;
    return obj;
}

QVariantMap AppEntry::toVariantMap() const
{
    return {
        {QStringLiteral("id"), id},
        {QStringLiteral("name"), name},
        {QStringLiteral("exePath"), exePath},
        {QStringLiteral("runtimeType"),
         runtimeType == Proton     ? QStringLiteral("proton")
             : runtimeType == Wine ? QStringLiteral("wine")
                                   : QStringLiteral("native")},
        {QStringLiteral("protonPath"), protonPath},
        {QStringLiteral("protonPrefix"), protonPrefix},
        {QStringLiteral("wineBinary"), wineBinary},
        {QStringLiteral("winePrefix"), winePrefix},
        {QStringLiteral("iconPath"), iconPath},
        {QStringLiteral("gridPath"), gridPath},
        {QStringLiteral("heroPath"), heroPath},
        {QStringLiteral("logoPath"), logoPath},
        {QStringLiteral("steamGridDbId"), steamGridDbId},
        {QStringLiteral("launchOptions"), launchOptions},
        {QStringLiteral("enableLogging"), enableLogging},
    };
}

AppEntry AppEntry::fromJson(const QJsonObject &obj)
{
    AppEntry e;
    e.id = obj[QStringLiteral("id")].toString();
    if (e.id.isEmpty())
        e.id = QUuid::createUuid().toString(QUuid::WithoutBraces);
    e.name = obj[QStringLiteral("name")].toString();
    e.exePath = obj[QStringLiteral("exePath")].toString();
    QString rt = obj[QStringLiteral("runtimeType")].toString();
    e.runtimeType = rt == QStringLiteral("proton") ? Proton : rt == QStringLiteral("wine") ? Wine : Native;
    e.protonPath = obj[QStringLiteral("protonPath")].toString();
    e.protonPrefix = obj[QStringLiteral("protonPrefix")].toString();
    e.wineBinary = obj[QStringLiteral("wineBinary")].toString();
    e.winePrefix = obj[QStringLiteral("winePrefix")].toString();
    e.iconPath = obj[QStringLiteral("iconPath")].toString();
    e.gridPath = obj[QStringLiteral("gridPath")].toString();
    e.heroPath = obj[QStringLiteral("heroPath")].toString();
    e.logoPath = obj[QStringLiteral("logoPath")].toString();
    e.steamGridDbId = obj[QStringLiteral("steamGridDbId")].toInt(0);
    e.launchOptions = obj[QStringLiteral("launchOptions")].toString();
    e.enableLogging = obj[QStringLiteral("enableLogging")].toBool(false);
    return e;
}

void AppEntry::updateFromVariantMap(const QVariantMap &app)
{
    name = app[QStringLiteral("name")].toString();
    exePath = app[QStringLiteral("exePath")].toString();
    QString rt = app[QStringLiteral("runtimeType")].toString();
    runtimeType = rt == QStringLiteral("proton") ? AppEntry::Proton : rt == QStringLiteral("wine") ? AppEntry::Wine : AppEntry::Native;
    protonPath = app[QStringLiteral("protonPath")].toString();
    protonPrefix = app[QStringLiteral("protonPrefix")].toString();
    wineBinary = app[QStringLiteral("wineBinary")].toString();
    winePrefix = app[QStringLiteral("winePrefix")].toString();
    iconPath = app[QStringLiteral("iconPath")].toString();
    gridPath = app[QStringLiteral("gridPath")].toString();
    heroPath = app[QStringLiteral("heroPath")].toString();
    logoPath = app[QStringLiteral("logoPath")].toString();
    steamGridDbId = app.value(QStringLiteral("steamGridDbId"), 0).toInt();
    launchOptions = app[QStringLiteral("launchOptions")].toString();
    enableLogging = app.value(QStringLiteral("enableLogging"), false).toBool();
}
