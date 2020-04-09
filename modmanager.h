#ifndef MODMANAGER_H
#define MODMANAGER_H

#include <QDir>
#include <QFile>

#include "mod/forgemod.h"
#include "mod/unknownmod.h"

class ModManager
{
private:
    QVector<IMod*> _mod_list;

    QString _mod_path;

    void append(const QString &path);

public:
    ModManager(const QString &path);
    ~ModManager();

    void setPath(const QString &path);

    bool install(const QString &path);
    bool remove(const int index);

    QString at(const int index, const QString &name);
    int count();

    void update();
    void clear();

    QPixmap logo(const int index);
};

#endif //MODMANAGER_H
