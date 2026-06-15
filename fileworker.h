#ifndef FILEWORKER_H
#define FILEWORKER_H

#include <QObject>
#include <QFile>
#include <QAtomicInteger>
#include <QMutex>

class FileWorker : public QObject
{
    Q_OBJECT

public:

    explicit FileWorker(QObject *parent=nullptr);

    void setInputFile(QString);
    void setOutputFile(QString);
    void setKey(quint64);


public slots:

    void process();
    void pause();
    void resume();
    void stop();


signals:

    void progress(qint64,qint64);
    void finished();
    void error(QString);


private:

    QString input;
    QString output;

    quint64 key;

    QAtomicInteger<bool> paused;
    QAtomicInteger<bool> stopped;

    QMutex mutex;
};

#endif
