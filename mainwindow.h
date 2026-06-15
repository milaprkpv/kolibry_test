#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QThread>

#include "filescanner.h"
#include "configmanager.h"
#include "taskqueue.h"
#include "resumemanager.h"
#include "fileworker.h"


QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    explicit MainWindow(QWidget *parent=nullptr);

    ~MainWindow();


private slots:

    void startProcessing();

    void scanFiles();

    void updateProgress(qint64,qint64);

    void pauseProcessing();

    void resumeProcessing();

    void stopProcessing();


private:

    Ui::MainWindow *ui;


    ConfigManager config;

    FileScanner scanner;

    TaskQueue queue;

    ResumeManager resume;


    QThread *workerThread;

    FileWorker *worker;


    QTimer timer;


};

#endif
