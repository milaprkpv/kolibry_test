#include "fileworker.h"

#include <QDataStream>


FileWorker::FileWorker(QObject *parent)
    :QObject(parent)
{
    paused=false;
    stopped=false;
}


void FileWorker::process()
{

    QFile in(input);

    if(!in.open(QIODevice::ReadOnly))
    {
        emit error("Cannot open input");
        return;
    }


    QFile out(output);


    if(!out.open(QIODevice::WriteOnly))
    {
        emit error("Cannot create output");
        return;
    }


    qint64 size=in.size();
    qint64 done=0;


    const int BLOCK=1024*1024;

    QByteArray buffer;


    while(!in.atEnd())
    {

        if(stopped)
            break;


        while(paused)
            QThread::msleep(100);



        buffer=in.read(BLOCK);


        quint64 *ptr=
        reinterpret_cast<quint64*>(buffer.data());


        int count=buffer.size()/8;


        for(int i=0;i<count;i++)
        {
            ptr[i]^=key;
        }


        out.write(buffer);


        done+=buffer.size();


        emit progress(done,size);

    }


    in.close();
    out.close();


    emit finished();
}



void FileWorker::pause()
{
    paused=true;
}


void FileWorker::resume()
{
    paused=false;
}


void FileWorker::stop()
{
    stopped=true;
}
