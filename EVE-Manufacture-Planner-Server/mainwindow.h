#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFile>
#include<QStringListModel>
#include <QThread>

#include <datamodel.h>
#include <productionview.h>
#include <planetaryview.h>
#include <dataloadworker.h>

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

public slots:
void errorString(QString es);
void on_DataReady(DataModel dm);


private:
    Ui::MainWindow *ui;
    PlanetaryView m_PlanetView;
    ProductionView m_ProdView;
    DataModel m_DM;
    QStringListModel *PISelectionModel;
};
#endif // MAINWINDOW_H
