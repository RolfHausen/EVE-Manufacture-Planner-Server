#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{    
    ui->setupUi(this);

    DataLoadWorker* worker = new DataLoadWorker();
    QThread* t1 = new QThread();

    //uncomment the next line if you want to check if the created thread and the mainthread have different addresses
    //QThread* mainthread = QCoreApplication::instance()->thread();
    //to check if they are different use breakpoint here. if it's right the addresses should be different

    worker->moveToThread(t1);
    connect(worker, SIGNAL(error(QString)),this,SLOT(errorString(QString)));
    connect(t1, SIGNAL(started()),worker,SLOT(process()));
    connect(worker, SIGNAL(finished()),t1,SLOT(quit()));
    connect(worker, SIGNAL(finished()),worker, SLOT(deleteLater()));
    connect(t1, SIGNAL(finished()),t1,SLOT(deleteLater()));

    qRegisterMetaType<DataModel>("DataModel");

    connect(worker, SIGNAL(deployData(DataModel)),this,SLOT(on_DataReady(DataModel)));

    t1->start();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_PlanetsPushButton_clicked()
{    
    m_PlanetView.exec();
}


void MainWindow::on_ProductionPushButton_clicked()
{    
    m_ProdView.exec();
}

void MainWindow::errorString(QString es)
{
    //temporary handling this via qdebug
    qDebug() << es;
}

void MainWindow::on_DataReady(DataModel dm)
{
    m_ProdView.setDataModel(dm);
    m_ProdView.ShowData();
}
