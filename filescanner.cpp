#include "filescanner.h"

#include <QDir>


void FileScanner::setPath(QString p)
{
    path=p;
}


void FileScanner::setMask(QString m)
{
    mask=m;
}



QStringList FileScanner::scan()
{

    QDir dir(path);


    QStringList filters;


    filters << mask;



    return dir.entryList(
        filters,
        QDir::Files
    );

}
