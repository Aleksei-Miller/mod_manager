#include "forgemod.h"

ForgeMod::ForgeMod(const QString &path)
{
    QZipReader zip(path, QIODevice::ReadOnly);

    if (zip.status() != QZipReader::NoError)
        return;

    QByteArray data = zip.fileData("mcmod.info");

    //mcmod.info
    if (!data.isEmpty())
    {
        //Path
        _map.insert("path", path);

        //Parse JSON
        QJsonDocument json_doc = QJsonDocument::fromJson(data);
        if (json_doc.isEmpty())
            return;

        QJsonObject root;

        QJsonArray json_array = json_doc.array();
        if (!json_array.isEmpty())
        {
            root = json_array[0].toObject();
            if (root.isEmpty())
                return;
        }
        //[ModList]
        else
        {
            QJsonObject json_object = json_doc.object();
            if (json_object.isEmpty())
                return;

            QJsonArray json_mod_list = json_object["modList"].toArray();
            root = json_mod_list[0].toObject();
        }

        _map.insert("modid", root["modid"].toString());
        _map.insert("name", root["name"].toString());

        _map.insert("description", root["description"].toString());
        _map.insert("version", root["version"].toString());
        _map.insert("mcversion", root["mcversion"].toString());
        _map.insert("url", root["url"].toString());

        //Authors
        QStringList author_list;

        foreach(QJsonValue author, root["authorList"].toArray())
            author_list.append(author.toString());

        _map.insert("authorList", author_list.join(','));

        //Credits
        _map.insert("credits", root["credits"].toString());

        //Logo
        QString logo_path = root["logoFile"].toString();
        _logo.loadFromData(zip.fileData(logo_path));
    }

    zip.close();
}

ForgeMod::~ForgeMod()
{
}

QString ForgeMod::value(const QString &key)
{
    return _map.value(key);
}


QPixmap ForgeMod::logo()
{
    return _logo;
}

bool ForgeMod::check(const QString &path)
{
    QZipReader zip(path, QIODevice::ReadOnly);

    if (zip.status() != QZipReader::NoError)
        return false;

    QByteArray data = zip.fileData("mcmod.info");

    //mcmod.info
    if (!data.isEmpty())
        return  true;

    return false;
}
