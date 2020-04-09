#include "modmanager.h"

ModManager::ModManager(const QString &path)
{
    _mod_path = path;
}

ModManager::~ModManager()
{
    clear();
}

void ModManager::clear()
{
    foreach(auto *mod, _mod_list)
        delete mod;

    _mod_list.clear();
}

void ModManager::update()
{
    clear();

    QDir dir(_mod_path);
    QStringList file_name_list = dir.entryList(QStringList() << "*.jar" << "*.zip",
                                               QDir::Files);

    foreach(auto file_name, file_name_list)
        append(_mod_path + "/" + file_name);
}

void ModManager::setPath(const QString &path)
{
    _mod_path = path;
}

void ModManager::append(const QString &path)
{
    if (ForgeMod::check(path))
    {
        ForgeMod *mod = new ForgeMod(path);
        _mod_list.append(mod);
    }
    else
    {
        UnknownMod *mod = new UnknownMod(path);
        _mod_list.append(mod);
    }
}

QPixmap ModManager::logo(const int index)
{
    return _mod_list.at(index)->logo();
}

bool ModManager::install(const QString &path)
{
    if (!QFile::exists(path))
        return false;

    //??
    QFileInfo fi(path);
    QString new_path = _mod_path + "/" + fi.fileName();

    //??
    if (!QFile::copy(path, new_path))
        return false;

    append(new_path);

    return true;
}

bool ModManager::remove(const int index)
{
    QString path = _mod_list.at(index)->value("path");

    if (!QFile::remove(path))
        return false;

    //
    delete _mod_list.at(index);
   _mod_list.removeAt(index);

   return true;
}

QString ModManager::at(const int index, const QString &name)
{
    return _mod_list.at(index)->value(name);
}

int ModManager::count()
{
    return _mod_list.count();
}
