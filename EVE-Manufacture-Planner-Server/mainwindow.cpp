#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{    
    ui->setupUi(this);


}

MainWindow::~MainWindow()
{
    delete ui;
}




void MainWindow::on_PlanetsPushButton_clicked()
{
    PlanetaryView p;
    p.exec();
}


void MainWindow::on_ProductionPushButton_clicked()
{
    ProductionView p;
    p.exec();
}

