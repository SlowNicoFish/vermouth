#pragma once

#include <QHash>
#include <QStringList>

const QHash<QString, QStringList> &platformCoreMap();
QStringList retroarchCoreDirs(const QString &retroarchBinary);
