#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <QSqlDatabase>
#include <QString>
#include <QSqlQuery>
#include <QDebug>
#include <QSqlError>
#include <QSqlRecord>
#include <QSqlQueryModel>

class DbManager : public QObject
{
    Q_OBJECT
public:
    DbManager();
    void setDBServer(QString dbserver);
    void setDBName(QString dbname);
    void setDBUser(QString dbuser);
    void setDBpwd(QString dbpwd);

    bool openDB();
    QStringList LoadTables();
    QStringList LoadTableRows(QString table);
    QSqlQueryModel* GetTableData();
    bool StoreFile(QString itemname, QString tablename, QString filename, QByteArray filedata);
    QString LastError();

signals:
    void progressChanged(int value);

private:
    QString m_DBServer;
    QString m_DBName;
    QString m_DBUser;
    QString m_DBPwd;
    QSqlDatabase m_DB;
    QStringList m_currentColumnNames;
    QStringList m_Errors;
    QSqlQueryModel m_currentTableData;
};

#endif // DBMANAGER_H
