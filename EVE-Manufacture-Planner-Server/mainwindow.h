#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFile>
#include<QStringListModel>
#include "datamodel.h"
#include "productionview.h"
#include "planetaryview.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

void on_PlanetsPushButton_clicked();

void on_ProductionPushButton_clicked();

private:
    Ui::MainWindow *ui;
    DataModel m_DM;
    QStringListModel *PISelectionModel;
};
#endif // MAINWINDOW_H
