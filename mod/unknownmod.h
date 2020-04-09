#ifndef UNKNOWNMOD_H
#define UNKNOWNMOD_H

#include <QFileInfo>
#include <QPixmap>

#include "imod.h"

class UnknownMod : public IMod
{
private:
    QString _name;
    QString _path;

public:
    UnknownMod(const QString &path)
    {
        _path = path;

        QFileInfo fi(path);
        _name = fi.baseName();
    }

    ~UnknownMod(){}

    QString value(const QString &name)
    {
        if (name == "name")
            return _name;
        else
            if (name == "path")
                return _path;

        return "";
    }

    QPixmap logo(){ return QPixmap(); }

    bool check(const QString &){ return true; }
};

#endif
