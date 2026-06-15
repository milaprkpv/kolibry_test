#ifndef TASKQUEUE_H
#define TASKQUEUE_H


#include <QStringList>


class TaskQueue
{

public:

    void add(QString);

    QString take();


    bool empty();


private:

    QStringList files;

};


#endif
