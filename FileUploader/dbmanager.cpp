#include "dbmanager.h"

DbManager::DbManager()
{

}

void DbManager::setDBServer(QString dbserver)
{
    m_DBServer=dbserver;
}

void DbManager::setDBName(QString dbname)
{
    m_DBName=dbname;
}

void DbManager::setDBUser(QString dbuser)
{
    m_DBUser=dbuser;
}

void DbManager::setDBpwd(QString dbpwd)
{
    m_DBPwd=dbpwd;
}

bool DbManager::openDB()
{
    QString connectionTemplate = "DRIVER={libtdsodbc.so};SERVER=%1;DATABASE=%2;";
    QString connectionString = connectionTemplate.arg(m_DBServer,m_DBName);
    m_DB = QSqlDatabase::addDatabase("QODBC", "default");

    m_DB.setDatabaseName(connectionString);
    m_DB.setUserName(m_DBUser);
    m_DB.setPassword(m_DBPwd);
    if (m_DB.open())
    {
        qDebug() << "Database connection ok";
        return true;
    }
    else
    {
        //2DO: Optimze output --> qDebug just for now
        qDebug() << m_DB.lastError();
    }
    return false; // if this is reached somthing went wrong.
}

QStringList DbManager::LoadTables()
{
    QStringList TableNames;
    QSqlQuery query("SELECT table_name,table_type FROM information_schema.tables ORDER BY table_name ASC;",m_DB);
    while (query.next())
    {
        if(query.value(1)=="BASE TABLE")
        {
            TableNames.append(query.value(0).toString());
        }
    }

    return  TableNames;
}

QStringList DbManager::LoadTableRows(QString table)
{
    QStringList TableRows;
    m_currentColumnNames.clear(); //clean up in case of a switch to another table
    QSqlQuery query(m_DB);    
    query.prepare("SELECT COLUMN_NAME FROM INFORMATION_SCHEMA.COLUMNS WHERE TABLE_NAME = (:tableName) ORDER BY 1");
    query.bindValue(":tableName",table);
    if(query.exec())
    {
        while (query.next())
        {
            m_currentColumnNames.append(query.value(0).toString());
        }

        QString columnName;

        for(int i=0;i<m_currentColumnNames.size();i++)
        {
            if(m_currentColumnNames[i].contains("Name"))
            {
                columnName = m_currentColumnNames[i];
            }
        }

        QString queryString ="Select * FROM " + table;

        m_currentTableData.setQuery(queryString,m_DB);
        if(query.exec(queryString))
        {            
            while (query.next())
            {                
                TableRows.append(query.value(columnName).toString());
            }
        }
        else
        {
            m_Errors.append(query.lastError().text());
        }
    }
    else
    {
        m_Errors.append(query.lastError().text());
    }
    return  TableRows;
}

QSqlQueryModel* DbManager::GetTableData()
{
    return &m_currentTableData;
}

bool DbManager::StoreFile(QString itemname,QString tablename, QString filename, QByteArray filedata)
{
    bool success=false;
    //reduce filname to only filename without path

    QStringList filenameSplit = filename.split("/");
    filename = filenameSplit.last();
    emit this->progressChanged(25);
    QString itemnameColumn;
    QString filenameColumnName,dataColumnName;
    for(int i=0;i<m_currentColumnNames.size();i++)
    {
        if(m_currentColumnNames[i].contains("ImageFile"))
        {
            dataColumnName=m_currentColumnNames[i];
        }
        else if(m_currentColumnNames[i].contains("Image"))
        {
            filenameColumnName=m_currentColumnNames[i];
        }
        else if(m_currentColumnNames[i].contains("Name"))
        {
           itemnameColumn=m_currentColumnNames[i];
        }
    }
    emit this->progressChanged(50);
    QSqlQuery query(m_DB);

    QString querytemplate= "UPDATE %1 SET %2='%3',%4=? where %5='%6'";
    QString querystring=querytemplate.arg(tablename,filenameColumnName,filename,dataColumnName,itemnameColumn,itemname);

    query.prepare(querystring);
    query.addBindValue(filedata);
    emit this->progressChanged(75);
    if(query.exec())
    {
        success=true;
        emit progressChanged(100);
        qDebug() <<"upload done";
    }
    else
    {
        m_Errors.append(query.lastError().text());
        emit this->progressChanged(0);

    }
    return success;
}

QString DbManager::LastError()
{
    return m_Errors.last();
}
