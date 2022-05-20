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
    bool success = false;
    //first template is for execution based on a Linux system
    //QString connectionTemplate = "DRIVER={libtdsodbc.so};SERVER=%1;DATABASE=%2;";
    //following template is for execution on an Windows-System.

    //Note maybe later configure this in a config File because only the Driverselection differs.
    QString connectionTemplate = "DRIVER={SQL SERVER};SERVER=%1;DATABASE=%2;";
    QString connectionString = connectionTemplate.arg(m_DBServer,m_DBName);
    m_DB = QSqlDatabase::addDatabase("QODBC", "default");

    m_DB.setDatabaseName(connectionString);
    m_DB.setUserName(m_DBUser);
    m_DB.setPassword(m_DBPwd);    
    if (m_DB.open())
    {
        qDebug() << "Database connection ok";
        success = true;
    }
    else
    {
        //2DO: Optimze output --> qDebug just for now
        qDebug() << m_DB.lastError();
        success = false;
    }
    return success;
}

PIData DbManager::loadPIProducts()
{
    PIData data;

    QSqlQuery query("SELECT PIID,PIName,PISize,PIIngredient_1,PIIngredient_2,PIIngredient_3,PIPx,PIIngredientamount,PIQuantity,PIImage,PIImageFile FROM PI_Product",m_DB);

    while (query.next())
    {
        PIProduct p;
        int id = 0;
        id = query.value("PIID").toInt();
        QString name = query.value("PIName").toString();

        float size = query.value("PISize").toFloat();

        //Ingredients can be null because not every product has them. e.g. P0 has no Ingredients
        if(!query.value("PIIngredient_1").isNull())
        {
            p.setIngredient(data.getbyId(query.value("PIIngredient_1").toInt()),1);
        }
        if(!query.value("PIIngredient_2").isNull())
        {
            p.setIngredient(data.getbyId(query.value("PIIngredient_2").toInt()),2);
        }
        if(!query.value("PIIngredient_3").isNull())
        {
            p.setIngredient(data.getbyId(query.value("PIIngredient_3").toInt()),3);
        }
        QString grade = query.value("PIPx").toString();
        int amount = query.value("PIIngredientamount").toInt();
        int quantity = query.value("PIQuantity").toInt();
        QString filename = query.value("PIImage").toString();
        QByteArray filedata = query.value("PIImageFile").toByteArray();

        p.setPIID(id);
        p.setPIName(name);
        p.setPiSize(size);

        p.setPIGrade(grade);
        p.setPIIngredientAmount(amount);
        p.setPIQuantity(quantity);
        p.setPIFile(filename,filedata);

        data.Add(p);
    }

    return data;
}

QList<Planet*> DbManager::loadPlanetaryData()
{
    QList<Planet*> Planets;
    QSqlQuery query(m_DB);
//    //here we make a querystring to get this long query more readable and manageable
    QString querystring = "SELECT";
    querystring.append(" PlName,");
    querystring.append(" PLSystemname,");
    querystring.append(" PLType,");
    //now we write an as clause for the Source to indentify the data for each foreign key
    querystring.append(" S1.SOName as 'S1.SOName',");
    querystring.append(" S1.SODensity as 'S1.SODensity',");
    querystring.append(" S2.SOName as 'S2.SOName',");
    querystring.append(" S2.SODensity as 'S2.SODensity',");
    querystring.append(" S3.SOName as 'S3.SOName',");
    querystring.append(" S3.SODensity as 'S3.SODensity',");
    querystring.append(" S4.SOName as 'S4.SOName',");
    querystring.append(" S4.SODensity as 'S4.SODensity',");
    querystring.append(" S5.SOName as 'S5.SOName',");
    querystring.append(" S5.SODensity as 'S5.SODensity'");
    querystring.append(" FROM Planet");
    //we make a inner join for each key as if it would be different tables
    //this way we get one pair of data for each db foreignkey.
    // this is not normalized to one FK because it is always 5 Sources on one planet
    // and all are read or written at the same time.
    querystring.append(" INNER JOIN Source S1 on PLSource_1 = S1.SOID");
    querystring.append(" INNER JOIN Source S2 on PLSource_2 = S2.SOID");
    querystring.append(" INNER JOIN Source S3 on PLSource_3 = S3.SOID");
    querystring.append(" INNER JOIN Source S4 on PLSource_4 = S4.SOID");
    querystring.append(" INNER JOIN Source S5 on PLSource_5 = S5.SOID");

    if(!query.exec(querystring))
    {
        m_Errors.append(query.lastError().text());
        qDebug() << m_Errors.last();
        return Planets; //returns an Empty List in Errorcase --> Later maybe exception.
    }

    while(query.next())
    {
        Planet *p = new Planet();
        p->setPlanetName(query.value("PLName").toString());
        p->setSystemName(query.value("PLSystemname").toString());

        const QMetaObject* metaObj = p->metaObject();
        QMetaEnum e = metaObj->enumerator(metaObj->indexOfEnumerator("PlanetTypes"));
        //conversion to char*
        QByteArray ba = query.value("PLType").toByteArray();
        const char *ctype = ba.data();

        p->setPlanetType(static_cast<Planet::PlanetTypes>(e.keysToValue(ctype)));

        p->addSource(query.value("S1.SOName").toString(),query.value("S1.SODensity").toInt());
        p->addSource(query.value("S2.SOName").toString(),query.value("S2.SODensity").toInt());
        p->addSource(query.value("S3.SOName").toString(),query.value("S3.SODensity").toInt());
        p->addSource(query.value("S4.SOName").toString(),query.value("S4.SODensity").toInt());
        p->addSource(query.value("S5.SOName").toString(),query.value("S5.SODensity").toInt());

        Planets.append(p);
    }

    return Planets;

}

bool DbManager::savePlanet(Planet& planet)
{
    bool success = false;
    bool hasErrors = false;
    unsigned int SOIDs[5] = {0,0,0,0,0};
    QSqlQuery query(m_DB);
    if(GetPlanetIDIfExists(planet)>0)
    {
        //as we found this via PlanetName and SystemName we don't write that again.
        //but Type and all other fields will be updated but ignoring Imagefilename and File.
        //because planet has only a FK to sources we need to join Sources into the Update

        //2DO We do Insert first to get Data in the DB with Data it is easier to make the update statement
        //query.prepare("Update Planet SET PLType = :type,PLSource_1 = :source1,PLSource_2 = :source2,PLSource_3 = :source3,PLSource_4 = source4,PLSource_5 = source5 Where PLID =:id");
        //query.bindValue(":type",p.PlanetType()); //this needs to be reworked because this will not post the key string i guess        

    }
    else
    {
        //we make a new DB Entry

        //because the Sources are in referential integritty they must be inserted first
        //so we need to iterate through our QMap.

        QMapIterator<QString,uint> SourcesIterator(planet.getSources());
        while(SourcesIterator.hasNext() && !hasErrors)
        {
            //write each source to Source - Table
            SourcesIterator.next();

            query.prepare("INSERT INTO Source(SOName,SODensity) VALUES(:name,:value)");
            query.bindValue(":name",SourcesIterator.key());
            query.bindValue(":value",SourcesIterator.value());

            if(!query.exec())
            {
                //if any errors occure append it to our Errorcollector
                m_Errors.append(query.lastError().text());
                //and stop the writing by setting hasErrors --> the loop will stop also
                hasErrors=true;
            }
        }

        if(!hasErrors)
        {
            //now we need to find the IDs of the values we have inserted first to set them later in the Planet - Table
            //this way we get the IDs in correct order instead of using ORDER BY DESC
            if (query.exec("SELECT SOID FROM Source WHERE SOID>(SELECT max(SOID)-5 FROM Source)"))
            {
                int j=0;
                while (query.next())
                {
                    SOIDs[j]= query.value("SOID").toUInt();
                    j++;
                }
            }
            else
            {
                //if anything wierd happens we add the Error Message to our Errorcollector
                m_Errors.append(query.lastError().text() + " Check Database for written false Data at Source Table or inform your DB Admin about it!");
                //and also now we need to fail the writing
                //at this state it would be worse case because then vaues are already written
                success = false;
                return success;
            }
            //next we insert the Planet itself into Database
            query.prepare("INSERT INTO Planet(PLName,PLSystemname,PLType,PLSource_1,PLSource_2,PLSource_3,PLSource_4,PLSource_5)VALUES(:name,:system,:type,:s1,:s2,:s3,:s4,:s5)");
            query.bindValue(":name",planet.PlanetName());
            query.bindValue(":system",planet.SystemName());

            //quick conversion of the TypeEnum to string

            const QMetaObject* metaObj = planet.metaObject();
            QMetaEnum e = metaObj->enumerator(metaObj->indexOfEnumerator("PlanetTypes"));
            QString type = e.key(planet.PlanetType());

            query.bindValue(":type",type);

            query.bindValue(":s1",SOIDs[0]);
            query.bindValue(":s2",SOIDs[1]);
            query.bindValue(":s3",SOIDs[2]);
            query.bindValue(":s4",SOIDs[3]);
            query.bindValue(":s5",SOIDs[4]);

            //This is for Logging purpose later
//            QString str = query.lastQuery();
//            QMapIterator<QString, QVariant> it(query.boundValues());
//             while (it.hasNext())
//             {
//                it.next();
//                str.replace(it.key(),it.value().toString());
//             }
//             qDebug() << str;

            if(!query.exec())
            {
                //if any error occured append it to our Errorcollector
                m_Errors.append(query.lastError().text());
                success = false;
            }
        }
    }
    return success;
}

int DbManager::GetPlanetIDIfExists(Planet& p)
{
    int PlanetId = 0;

    QSqlQuery query(m_DB);
    query.prepare("SELECT PLID FROM Planet WHERE PLName = ':name' AND PLSystemname = ':system' ");
    query.bindValue(":name", p.PlanetName());
    query.bindValue(":system",p.SystemName());

    if (query.exec())
    {
       if (query.next())
       {
          // it exists
           PlanetId = query.value("PLID").toUInt();
       }
    }
    else
    {
        m_Errors.append(query.lastError().text());
    }
    return PlanetId;
}

QString DbManager::LastError()
{

    return m_Errors.last();
}
