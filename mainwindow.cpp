#include "mainwindow.h"
#include "ui_mainwindow.h"


#include <QMessageBox>


MainWindow::MainWindow(QWidget *parent)
    :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);


    config.load();


    connect(&timer,
            &QTimer::timeout,
            this,
            &MainWindow::scanFiles);


    connect(ui->startButton,
            &QPushButton::clicked,
            this,
            &MainWindow::startProcessing);


    connect(ui->pauseButton,
            &QPushButton::clicked,
            this,
            &MainWindow::pauseProcessing);


    connect(ui->resumeButton,
            &QPushButton::clicked,
            this,
            &MainWindow::resumeProcessing);


    connect(ui->stopButton,
            &QPushButton::clicked,
            this,
            &MainWindow::stopProcessing);

}



MainWindow::~MainWindow()
{

    stopProcessing();

    config.save();

    delete ui;
}



void MainWindow::startProcessing()
{

    scanner.setPath(
        config.inputPath()
    );


    scanner.setMask(
        config.mask()
    );


    scanFiles();

}



void MainWindow::scanFiles()
{

    QList<QString> files =
            scanner.scan();


    for(auto &f:files)
        queue.add(f);



    if(queue.empty())
        return;



    QString file=
            queue.take();



    workerThread=new QThread;

    worker=new FileWorker;


    worker->setInputFile(file);


    worker->setOutputFile(
        config.outputPath()
    );


    worker->setKey(
        config.key()
    );


    worker->moveToThread(workerThread);


    connect(workerThread,
            &QThread::started,
            worker,
            &FileWorker::process);


    connect(worker,
            &FileWorker::progress,
            this,
            &MainWindow::updateProgress);


    connect(worker,
            &FileWorker::finished,
            workerThread,
            &QThread::quit);



    connect(workerThread,
            &QThread::finished,
            worker,
            &QObject::deleteLater);



    workerThread->start();

}



void MainWindow::updateProgress(qint64 done,qint64 total)
{

    int percent =
            (done*100)/total;


    ui->progressBar
            ->setValue(percent);


    ui->statusLabel
            ->setText(
                QString("%1 / %2 bytes")
                .arg(done)
                .arg(total)
                );

}



void MainWindow::pauseProcessing()
{

    if(worker)
        worker->pause();

}


void MainWindow::resumeProcessing()
{

    if(worker)
        worker->resume();

}


void MainWindow::stopProcessing()
{

    if(worker)
        worker->stop();


    if(workerThread)
    {
        workerThread->quit();
        workerThread->wait();
    }

}
