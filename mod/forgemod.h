#ifndef FORGEMOD_H
#define FORGEMOD_H

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>

#include <QMap>
#include <QPixmap>

#include <QDebug>

#include "qzipreader_p.h"

#include "imod.h"

class ForgeMod : public IMod
{
public:
    ForgeMod(const QString &path);
    ~ForgeMod();

    QString value(const QString &key);
    QPixmap logo();

    static bool check(const QString &path);

private:
    QMap<QString, QString> _map;

    QPixmap _logo;
};

#endif // FORGEMOD_H
