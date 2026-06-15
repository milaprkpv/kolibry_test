#ifndef FILESCANNER_H
#define FILESCANNER_H


#include <QString>
#include <QStringList>


class FileScanner
{

public:

    void setPath(QString);

    void setMask(QString);


    QStringList scan();


private:

    QString path;

    QString mask;

};


#endif
