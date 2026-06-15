#ifndef CONFIGMANAGER_H
#define CONFIGMANAGER_H


#include <QString>


class ConfigManager
{

public:


    void load();

    void save();



    QString inputPath();

    QString outputPath();

    QString mask();


    quint64 key();



private:


    QString in;

    QString out;

    QString fileMask;


    quint64 xorKey;


};


#endif
