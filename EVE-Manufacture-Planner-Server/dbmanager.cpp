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

    QSqlQuery query("SELECT PIID,PIName,PISize,PIIngredient_1,PIIngredient_2,PIIngredient_3,PIPx,PIIngredientamount,PIQuantity,PIImage,PIImageFile FROM PIProduct",m_DB);

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
            PIProduct* ingredient = data.getbyId(query.value("PIIngredient_1").toInt());
            if(ingredient != nullptr)
            {
                p.setIngredient(ingredient,1);
            }
        }
        if(!query.value("PIIngredient_2").isNull())
        {
            PIProduct* ingredient = data.getbyId(query.value("PIIngredient_2").toInt());
            if(ingredient != nullptr)
            {
                p.setIngredient(ingredient,2);
            }
        }
        if(!query.value("PIIngredient_3").isNull())
        {
            PIProduct* ingredient = data.getbyId(query.value("PIIngredient_3").toInt());
            if(ingredient != nullptr)
            {
                p.setIngredient(ingredient,3);
            }
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

        //this is for converting the Enum into string
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

QList<AbyssalMaterial> DbManager::LoadAbyssalMaterials()
{
    QSqlQuery query(m_DB);
    QList<AbyssalMaterial> Abyssals;
    if(query.exec("SELECT AMID,AMName,AMSize,AMGroup FROM AbyssalMaterial"))
    {
        while(query.next())
        {
            AbyssalMaterial am;
            am.setAMID(query.value("AMID").toUInt());
            am.setAMName(query.value("AMName").toString());
            am.setAMSize(query.value("AMSize").toFloat());
            am.setAMGroup(query.value("AMGroup").toString());
            Abyssals.append(am);
        }
    }
    else
    {
        m_Errors.append(query.lastError().text());
    }

    return Abyssals; //in case of an Error this list is Empty;

}

QList<Commodity> DbManager::LoadCommodities()
{
    QSqlQuery query(m_DB);
    QList<Commodity> Commodities;
    if(query.exec("SELECT COID,COName,COSize,COGroup,COBPID FROM Commodity"))
    {
        while (query.next())
        {
            Commodity comm;
            comm.setCOID(query.value("COID").toUInt());
            comm.setCOName(query.value("COName").toString());
            comm.setCOSize(query.value("COSize").toFloat());
            comm.setCOGroup(query.value("COGroup").toString());
            comm.setCOBPID(query.value("COBPID").toUInt());
            Commodities.append(comm);
        }
    }
    else
    {
        m_Errors.append(query.lastError().text());
    }
    return Commodities;
}

QList<FuelBlock> DbManager::LoadFuelBlocks()
{
    QSqlQuery query(m_DB);
    QList<FuelBlock> FuelBlocks;
    if(query.exec("SELECT FBID,FBName,FBSize,FBGroup,FBBPID FROM FuelBlock"))
    {
        while (query.next())
        {
            FuelBlock fb;
            fb.setFBID(query.value("FBID").toUInt());
            fb.setFBName(query.value("FBName").toString());
            fb.setFBSize(query.value("FBSize").toFloat());
            fb.setFBGroup(query.value("FBGroup").toString());
            fb.setFBBPID(query.value("FBBPID").toUInt());
            FuelBlocks.append(fb);
        }
    }
    else
    {
        m_Errors.append(query.lastError().text());
    }
    return FuelBlocks;

}

QList<Gas> DbManager::LoadGases()
{
    QSqlQuery query(m_DB);
    QList<Gas> Gases;
    if(query.exec("SELECT GID,GName,GSize,GGroup FROM Gas"))
    {
        while (query.next())
        {
            Gas g;
            g.setGID(query.value("GID").toUInt());
            g.setGName(query.value("GName").toString());
            g.setGSize(query.value("GSize").toFloat());
            g.setGGroup(query.value("GGroup").toString());
            Gases.append(g);
        }
    }
    else
    {
        m_Errors.append(query.lastError().text());
    }
    return Gases;
}

QList<IceProduct> DbManager::LoadIceProducts()
{
    QSqlQuery query(m_DB);
    QList<IceProduct> IceProducts;
    if(query.exec("SELECT ICEID,ICEName,ICESize,ICEGroup FROM IceProduct"))
    {
        while (query.next())
        {
            IceProduct ice;
            ice.setIceID(query.value("ICEID").toUInt());
            ice.setIceName(query.value("ICEName").toString());
            ice.setIceSize(query.value("ICESize").toFloat());
            ice.setIceGroup(query.value("ICEGroup").toString());
            IceProducts.append(ice);
        }
    }
    else
    {
        m_Errors.append(query.lastError().text());
    }
    return IceProducts;
}

QList<Mineral> DbManager::LoadMinerals()
{
    QSqlQuery query(m_DB);
    QList<Mineral> Minerals;
    if(query.exec("SELECT MINID,MINName,MINSize,MINGroup FROM Mineral"))
    {
        while (query.next())
        {
            Mineral min;
            min.setMinId(query.value("MINID").toUInt());
            min.setMinName(query.value("MINName").toString());
            min.setMinSize(query.value("MINSize").toFloat());
            min.setMinGroup(query.value("MINGroup").toString());
            Minerals.append(min);
        }
    }
    else
    {
        m_Errors.append(query.lastError().text());
    }
    return Minerals;
}

QList<MoonGoo> DbManager::LoadMoonGoos()
{
    QSqlQuery query(m_DB);
    QList<MoonGoo> MoonGoos;
    if(query.exec("SELECT MGID,MGName,MGSize,MGGroup FROM MoonGoo"))
    {
        while (query.next())
        {
            MoonGoo mg;            
            mg.setMGID(query.value("MGID").toUInt());
            mg.setMGName(query.value("MGName").toString());
            mg.setMGSize(query.value("MGSize").toFloat());
            mg.setMGGroup(query.value("MGGroup").toString());
            MoonGoos.append(mg);
        }
    }
    else
    {
        m_Errors.append(query.lastError().text());
    }
    return MoonGoos;
}

QList<NamedComponent> DbManager::LoadNamedComponents()
{
    QSqlQuery query(m_DB);
    QList<NamedComponent> NComps;
    if(query.exec("SELECT NCID,NCName,NCSize,NCGroup FROM NamedComponent"))
    {
        while (query.next())
        {
            NamedComponent nc;
            nc.setNCID(query.value("NCID").toUInt());
            nc.setNCName(query.value("NCName").toString());
            nc.setNCSize(query.value("NCSize").toFloat());
            nc.setNCGroup(query.value("NCGroup").toString());
            NComps.append(nc);
        }
    }
    else
    {
        m_Errors.append(query.lastError().text());
    }
    return NComps;
}

QList<ReactionMaterial> DbManager::LoadReactionMaterials()
{
    QSqlQuery query(m_DB);
    QList<ReactionMaterial> ReactionMats;
    if(query.exec("SELECT RMID,RMName,RMSize,RMGroup,RMBPID FROM ReactionMaterial"))
    {
        while (query.next())
        {
            ReactionMaterial rm;
            rm.setRMID(query.value("RMID").toUInt());
            rm.setRMName(query.value("RMName").toString());
            rm.setRMSize(query.value("RMSize").toFloat());
            rm.setRMGroup(query.value("RMGroup").toString());
            rm.setRMBPID(query.value("RMBPID").toUInt());
            ReactionMats.append(rm);
        }
    }
    else
    {
        m_Errors.append(query.lastError().text());
    }
    return ReactionMats;
}

QList<Salvage> DbManager::LoadSalvages()
{
    QSqlQuery query(m_DB);
    QList<Salvage> Salvages;
    if(query.exec("SELECT SALID,SALName,SALSize,SALGroup FROM Salvage"))
    {
        while (query.next())
        {
            Salvage s;
            s.setSALID(query.value("SALID").toUInt());
            s.setSALName(query.value("SALName").toString());
            s.setSALSize(query.value("SALSize").toFloat());
            s.setSALGroup(query.value("SAlGroup").toString());
            Salvages.append(s);
        }
    }
    else
    {
        m_Errors.append(query.lastError().text());
    }
    return  Salvages;
}

QList<T1Product> DbManager::LoadT1Products()
{
    QSqlQuery query(m_DB);
    QList<T1Product> T1Products;
    if(query.exec("SELECT T1ID,T1Name,T1Size,T1Group,T1BPID FROM T1Product"))
    {
        while (query.next())
        {
            T1Product t1;
            t1.setT1ID(query.value("T1ID").toUInt());
            t1.setT1Name(query.value("T1Name").toString());
            t1.setT1Size(query.value("T1Size").toFloat());
            t1.setT1Group(query.value("T1Group").toString());
            t1.setT1BPID(query.value("T1BPID").toUInt());
            T1Products.append(t1);
        }
    }
    else
    {
        m_Errors.append(query.lastError().text());
    }
    return T1Products;
}

QList<Blueprint> DbManager::LoadBlueprints()
{
    QSqlQuery query(m_DB);
    QList<Blueprint> Blueprints;
    //Now we get the plain data from the Blueprint itself before we get the data for each needed material
    if(query.exec("SELECT BPID,BPName,BPProduct,BPAmount,BPGroup,BPType,BPSize FROM Blueprint Order by BPGroup"))
    {
        while(query.next())
        {
            Blueprint Bp;
            Bp.setBPID(query.value("BPID").toUInt());
            Bp.setBPName(query.value("BPName").toString());
            Bp.setBPProduct(query.value("BPProduct").toString());
            Bp.setBPAmount(query.value("BPAmount").toUInt());
            Bp.setBPGroup(query.value("BPGroup").toString());
            Bp.setBPType(query.value("BPType").toString());
            Bp.setBPSize(query.value("BPSize").toFloat());

            Blueprints.append(Bp);
        }
    }
    else
    {
        m_Errors.append(query.lastError().text());
    }
    return Blueprints;
}

bool DbManager::LoadBlueprintMaterials(QList<AbyssalMaterial>& AbyssalMaterials,QList<Commodity>& Commodities,QList<FuelBlock>& FuelBlocks,QList<Gas>& Gases,QList<IceProduct>& IceProducts,QList<Mineral>& Minerals,QList<MoonGoo>& MoonGoos,QList<NamedComponent>& NamedComponents,PIData& Pdata,QList<ReactionMaterial>& ReactionMaterials,QList<Salvage>& Salvages,QList<T1Product>& T1Products,Blueprint& Blueprint)
{
    QSqlQuery query(m_DB);

        query.prepare("SELECT BPID,BPMMATID,BPMAmount,ItemID,MATGroup from BlueprintMaterialGroups Where BPID = :bpid");
        query.bindValue(":bpid",Blueprint.BPID());
        if(query.exec())
        {
            while(query.next()) //move through all lines of needed materials for the current blueprint
            {                
                //preprare the Data to be filled in.
                int ItemId = query.value("ItemID").toUInt();
                int ItemAmount = query.value("BPMAmount").toUInt();
                int MatId = query.value("BPMMATID").toUInt();

                if(query.value("MATGroup").toString()=="Mineral")
                {
                    for(int i=0;i<Minerals.count();i++)
                    {
                        if(Minerals[i].MinId()==ItemId)
                        {
                            Minerals[i].setMatId(MatId);
                            Material Mat(ItemAmount,Minerals[i],"Mineral");
                            Blueprint.AddMaterial(Mat);

                        }
                    }
                }
                else if(query.value("MATGroup").toString()=="IceProduct")
                {
                    for(int i=0;i<IceProducts.count();i++)
                    {
                        if(IceProducts[i].IceID()==ItemId)
                        {
                            IceProducts[i].setMatId(MatId);
                            Material Mat(ItemAmount,IceProducts[i],"IceProduct");
                            Blueprint.AddMaterial(Mat);

                        }
                    }
                }
                else if(query.value("MATGroup").toString()=="Gas")
                {
                    for(int i=0;i<Gases.count();i++)
                    {
                        if(Gases[i].GID()==ItemId)
                        {
                            Gases[i].setMatId(MatId);
                            Material Mat(ItemAmount,Gases[i],"Gas");
                            Blueprint.AddMaterial(Mat);

                        }
                    }
                }
                else if(query.value("MATGroup").toString()=="Salvage")
                {
                    for(int i=0;i<Salvages.count();i++)
                    {
                        if(Salvages[i].SALID()==ItemId)
                        {
                            Salvages[i].setMatId(MatId);
                            Material Mat(ItemAmount,Salvages[i],"Salvage");
                            Blueprint.AddMaterial(Mat);

                        }
                    }
                }
                else if(query.value("MATGroup").toString()=="PIProduct")
                {
                    PIProduct* pi = Pdata.getbyId(ItemId);
                    if(pi!=nullptr)
                    {
                        pi->setMatId(MatId);
                        Material Mat(ItemAmount,*pi,"PIProduct");
                        Blueprint.AddMaterial(Mat);
                    }

                }
                else if(query.value("MATGroup").toString()=="Commodity")
                {
                    for(int i=0;i<Commodities.count();i++)
                    {
                        if(Commodities[i].COID()==ItemId)
                        {
                            Commodities[i].setMatId(MatId);
                            Material Mat(ItemAmount,Commodities[i],"Commodity");
                            Blueprint.AddMaterial(Mat);

                        }
                    }
                }
                else if(query.value("MATGroup").toString()=="MoonGoo")
                {
                    for(int i=0;i<MoonGoos.count();i++)
                    {
                        if(MoonGoos[i].MGID()==ItemId)
                        {
                            MoonGoos[i].setMatId(MatId);
                            Material Mat(ItemAmount,MoonGoos[i],"MoonGoo");
                            Blueprint.AddMaterial(Mat);
                        }
                    }
                }
                else if(query.value("MATGroup").toString()=="Reaction")
                {
                    for(int i=0;i<ReactionMaterials.count();i++)
                    {
                        if(ReactionMaterials[i].RMID()==ItemId)
                        {
                            ReactionMaterials[i].setMatId(MatId);
                            Material Mat(ItemAmount,ReactionMaterials[i],"Reaction");
                            Blueprint.AddMaterial(Mat);
                        }
                    }
                }
                else if(query.value("MATGroup").toString()=="T1Product")
                {
                    for(int i=0;i<T1Products.count();i++)
                    {
                        if(T1Products[i].T1ID()==ItemId)
                        {
                            T1Products[i].setMatId(MatId);
                            Material Mat(ItemAmount,T1Products[i],"T1Product");
                            Blueprint.AddMaterial(Mat);
                        }
                    }
                }
                else if(query.value("MATGroup").toString()=="NamedComponent")
                {
                    for(int i=0;i<NamedComponents.count();i++)
                    {
                        if(NamedComponents[i].NCID()==ItemId)
                        {
                            NamedComponents[i].setMatId(MatId);
                            Material Mat(ItemAmount,NamedComponents[i],"NamedComponent");
                            Blueprint.AddMaterial(Mat);
                        }
                    }
                }
                else if(query.value("MATGroup").toString()=="FuelBlock")
                {
                    for(int i=0;i<FuelBlocks.count();i++)
                    {
                        if(FuelBlocks[i].FBID()==ItemId)
                        {
                            FuelBlocks[i].setMatId(MatId);
                            Material Mat(ItemAmount,FuelBlocks[i],"FuelBlock");
                            Blueprint.AddMaterial(Mat);
                        }
                    }
                }
                else if(query.value("MATGroup").toString()=="AbyssalMaterial")
                {
                    for(int i=0;i<AbyssalMaterials.count();i++)
                    {
                        if(AbyssalMaterials[i].AMID()==ItemId)
                        {
                            AbyssalMaterials[i].setMatId(MatId);
                            Material Mat(ItemAmount,AbyssalMaterials[i],"AbyssalMaterial");
                            Blueprint.AddMaterial(Mat);
                        }
                    }
                }
                else
                {
                    QString error="The Materialgroup:" + query.value("MATGroup").toString() + "at MATID: "+ QString::number(MatId) + " could not be solved. This could mean the Materialgroup is wrong or not implemented.";
                    m_Errors.append(error);
                    return false; //if one Group is false the whole list is not complete nor correct so we cancle immidietly
                }
            }
        }    
    return true;
}

QString DbManager::LastError()
{

    return m_Errors.last();
}
