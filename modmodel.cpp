#include "modmodel.h"

ModModel::ModModel(const QString &path)
{
    _mod_manager = new ModManager(path);

    _mod_manager->update();
}

ModModel::~ModModel()
{
    delete _mod_manager;
}

void ModModel::setPath(const QString &path)
{
    beginResetModel();

    _mod_manager->setPath(path);
    _mod_manager->update();

    endResetModel();
}

bool ModModel::append(const QString &path)
{
    if (!_mod_manager->install(path))
        return false;

    insertRow(0);

    return true;
}

bool ModModel::remove(const QModelIndex &index)
{
    if (!_mod_manager->remove(index.row()))
        return false;

    removeRow(index.row());

    return true;
}

QPixmap ModModel::logo(const QModelIndex &index)
{
    return _mod_manager->logo(index.row());
}


int ModModel::rowCount(const QModelIndex &) const
{
    return _mod_manager->count();
}

int ModModel::columnCount(const QModelIndex &) const
{
    return 8;
}

QVariant ModModel::data(const QModelIndex &index, int role) const
{
    if (role == Qt::DisplayRole)
    {
        switch(index.column())
        {
        case ModInfo::Name :
            return _mod_manager->at(index.row(), "name");

        case ModInfo::Description :
            return _mod_manager->at(index.row(), "description");

        case ModInfo::Version :
            return _mod_manager->at(index.row(), "version");

        case ModInfo::McVersion :
            return _mod_manager->at(index.row(), "mcversion");

        case ModInfo::Url :
            return _mod_manager->at(index.row(), "url");

        case ModInfo::AuthorList :
            return _mod_manager->at(index.row(), "authorList");

        case ModInfo::Credits :
            return _mod_manager->at(index.row(), "credits");

        case ModInfo::Path :
            return _mod_manager->at(index.row(), "path");
        }
    }

    return QVariant();
}

bool ModModel::insertRow(int row, const QModelIndex &parent)
{
    beginInsertRows(parent, row, row);
    endInsertRows();

    return true;
}

bool ModModel::removeRow(int row, const QModelIndex &parent)
{
    beginRemoveRows(parent, row, row);
    endRemoveRows();

    return true;
}
