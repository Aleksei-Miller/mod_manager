#ifndef MODMODEL_H
#define MODMODEL_H

#include <QAbstractTableModel>

#include "modmanager.h"

enum ModInfo
{
    Name,
    Description,
    Version,
    McVersion,
    Url,
    AuthorList,
    Credits,
    Path
};

class ModModel : public QAbstractTableModel
{
private:
    ModManager *_mod_manager;

    int rowCount(const QModelIndex & = QModelIndex()) const;
    int columnCount(const QModelIndex & = QModelIndex()) const;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;

    bool insertRow(int row, const QModelIndex &parent = QModelIndex());
    bool removeRow(int row, const QModelIndex &parent = QModelIndex());

public:
    ModModel(const QString &path);
    ~ModModel();

    void setPath(const QString &path);

    bool append(const QString &path);
    bool remove(const QModelIndex &index);

    QPixmap logo(const QModelIndex &index);
};

#endif
