#ifndef RESUMEMANAGER_H
#define RESUMEMANAGER_H


#include <QString>


class ResumeManager
{

public:


    void save(
        QString file,
        qint64 position
    );


    qint64 load(
        QString file
    );


private:

    QString database="resume.json";

};


#endif
