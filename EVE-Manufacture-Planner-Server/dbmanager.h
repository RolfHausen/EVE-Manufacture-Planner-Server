#ifndef DBMANAGER_H
#define DBMANAGER_H

#include "pidata.h"
#include "planet.h"

#include <QSqlDatabase>
#include <QString>
#include <QSqlQuery>
#include <QDebug>
#include <QSqlError>
#include <QSqlRecord>
#include <QMapIterator>

class DbManager
{
public:
    DbManager();
    void setDBServer(QString dbserver);
    void setDBName(QString dbname);
    void setDBUser(QString dbuser);
    void setDBpwd(QString dbpwd);

    bool openDB();
    PIData loadPIProducts();
    QList<Planet*> loadPlanetaryData();
    bool savePlanet(Planet& planet);
    int GetPlanetIDIfExists(Planet& p); //returns the ID if the Planet exists otherwiese Zero.

    QString LastError();
private:
    QString m_DBServer;
    QString m_DBName;
    QString m_DBUser;
    QString m_DBPwd;
    QSqlDatabase m_DB;
    QStringList m_Errors; //DB Errors will be added in here
};

#endif // DBMANAGER_H
