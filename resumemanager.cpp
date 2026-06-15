#include "resumemanager.h"

#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>


void ResumeManager::save(
        QString file,
        qint64 pos)
{

    QJsonObject obj;


    obj["file"]=file;

    obj["pos"]=QString::number(pos);


    QFile f(database);


    if(f.open(QIODevice::WriteOnly))
    {
        f.write(
        QJsonDocument(obj)
        .toJson()
        );
    }

}



qint64 ResumeManager::load(QString file)
{

    QFile f(database);


    if(!f.open(QIODevice::ReadOnly))
        return 0;



    auto obj=
    QJsonDocument::fromJson(
        f.readAll()
    ).object();



    if(obj["file"].toString()==file)

        return obj["pos"]
        .toString()
        .toLongLong();



    return 0;

}
