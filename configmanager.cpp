#include "configmanager.h"

#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>


void ConfigManager::load()
{

    QFile f("settings.json");


    if(!f.open(QIODevice::ReadOnly))
    {
        xorKey=0;
        return;
    }


    auto obj =
    QJsonDocument::fromJson(
        f.readAll()
    ).object();



    in=obj["input"].toString();

    out=obj["output"].toString();

    fileMask=obj["mask"].toString();


    xorKey=
    obj["key"].toString()
    .toULongLong(nullptr,16);

}



void ConfigManager::save()
{

    QJsonObject obj;


    obj["input"]=in;

    obj["output"]=out;

    obj["mask"]=fileMask;


    obj["key"]=
    QString::number(
        xorKey,
        16
    );


    QFile f("settings.json");


    if(f.open(QIODevice::WriteOnly))
    {
        f.write(
        QJsonDocument(obj)
        .toJson()
        );
    }

}



QString ConfigManager::inputPath()
{
    return in;
}


QString ConfigManager::outputPath()
{
    return out;
}


QString ConfigManager::mask()
{
    return fileMask;
}


quint64 ConfigManager::key()
{
    return xorKey;
}
