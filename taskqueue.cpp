#include "taskqueue.h"



void TaskQueue::add(QString f)
{
    if(!files.contains(f))
        files.append(f);
}



QString TaskQueue::take()
{

    if(files.isEmpty())
        return "";


    QString f=files.first();


    files.removeFirst();


    return f;

}



bool TaskQueue::empty()
{
    return files.isEmpty();
}
