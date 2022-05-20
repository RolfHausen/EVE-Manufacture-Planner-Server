#ifndef DATAMODEL_H
#define DATAMODEL_H

#include<QTreeWidgetItem>
#include <QFile>
#include<QStandardItemModel>
#include "dbmanager.h"
#include "planet.h"


class DataModel
{
public:
    DataModel();
    bool openDb();
    void closeDB();
    void LoadPIData();
    void LoadPlanetData();

    PIData getPIData();
    QStandardItemModel *getPlanetItemModel();
    QStringList getPIDataStringList();
    QStringList getPIDataByPGrade(PIGrades grade);
    void getPIDataTreeItem(QTreeWidget* parent,PIProduct p);
    QStringList getPlanetTypes();
    QStringList getBarrenSources();
    QStringList getGasSources();
    QStringList getIceSources();
    QStringList getLavaSources();
    QStringList getOceanicSources();
    QStringList getPlasmaSources();
    QStringList getStormSources();
    QStringList getTemperateSources();
    QString LastError();

    void SavePlanet(QString name,QString systemname,QString type,QMap<QString,uint> sources);

private:
    DbManager m_DbMan;
    QStringList m_Errors;
    QString readPwdFile();
    PIData m_PIData;
    QList<Planet*> m_Planets;

    QTreeWidgetItem* buildPIDataItemTree(QTreeWidgetItem* parent,PIProduct *p);

};

#endif // DATAMODEL_H
