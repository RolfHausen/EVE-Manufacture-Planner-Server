#include "datamodel.h"

DataModel::DataModel()
{
    //idea: change the textfile into an XML File and store complete DBConnection Data within
    QString userpwd =readPwdFile();
    m_DbMan.setDBServer("192.168.0.17,1433");
    m_DbMan.setDBName("EVE_Manufacture_Planner");
    m_DbMan.setDBUser("sa");
    m_DbMan.setDBpwd(userpwd);
}

bool DataModel::openDb()
{
    bool success = false;
    if(m_DbMan.openDB())
    {
        success = true;
    }
    else
    {
        m_Errors.append(m_DbMan.LastError());
        success = false;
    }
    return success;
}

void DataModel::closeDB()
{
    
}

void DataModel::LoadPIData()
{
    m_PIData= m_DbMan.loadPIProducts();
}

void DataModel::LoadPlanetData()
{
   m_Planets =  m_DbMan.loadPlanetaryData();
}

QStringList DataModel::getPIDataStringList()
{
    QStringList PINames;
    QList<PIProduct> PIProducts = m_PIData.getAll();
    for(int i=0;i<PIProducts.size();i++)
    {
        PINames.append(PIProducts[i].getPIName());
    }
    return PINames;
}

PIData DataModel::getPIData()
{
    return m_PIData;
}

QStandardItemModel* DataModel::getPlanetItemModel()
{
    const int ROWS = 17;
    const int COLUMNS = m_Planets.count();
    QStandardItemModel *model = new QStandardItemModel(ROWS,COLUMNS);

    model->setHeaderData( 0, Qt::Vertical, QObject::tr("Planetname") );
    model->setHeaderData( 1, Qt::Vertical, QObject::tr("Systemname") );
    model->setHeaderData( 2, Qt::Vertical, QObject::tr("PlanetType") );
    //Source - Columns
    model->setHeaderData( 3, Qt::Vertical, QObject::tr("Aqueous Liquids") );
    model->setHeaderData( 4, Qt::Vertical, QObject::tr("Autotrophs") );
    model->setHeaderData( 5, Qt::Vertical, QObject::tr("Base Metals") );
    model->setHeaderData( 6, Qt::Vertical, QObject::tr("Carbon Compounds") );
    model->setHeaderData( 7, Qt::Vertical, QObject::tr("Complex Organisms") );
    model->setHeaderData( 8, Qt::Vertical, QObject::tr("Felsic Magma") );
    model->setHeaderData( 9, Qt::Vertical, QObject::tr("Heavy Metals") );
    model->setHeaderData( 10, Qt::Vertical, QObject::tr("Ionic Solutions") );
    model->setHeaderData( 11, Qt::Vertical, QObject::tr("Micro Organisms") );
    model->setHeaderData( 12, Qt::Vertical, QObject::tr("Noble Gas") );
    model->setHeaderData( 13, Qt::Vertical, QObject::tr("Noble Metals") );
    model->setHeaderData( 14, Qt::Vertical, QObject::tr("Non-CS Crystals") );
    model->setHeaderData( 15, Qt::Vertical, QObject::tr("Planktic Colonies") );
    model->setHeaderData( 16, Qt::Vertical, QObject::tr("Reactive Gas") );
    model->setHeaderData( 17, Qt::Vertical, QObject::tr("Suspended Plasma") );

    for(int i=0; i<m_Planets.size();i++)
    {
        QModelIndex index = model->index(0,i,QModelIndex());
        model->setData(index,m_Planets[i]->PlanetName());

        index = model->index(1,i,QModelIndex());
        model->setData(index,m_Planets[i]->SystemName());

        index = model->index(2,i,QModelIndex());

        const QMetaObject* metaObj = m_Planets[i]->metaObject();
        QMetaEnum e = metaObj->enumerator(metaObj->indexOfEnumerator("PlanetTypes"));
        QString type = e.key(m_Planets[i]->PlanetType());
        model->setData(index,type);


        //for the sources we have to identify the column where the sourcedata needs to be placed within the table
        //this is because different types of planets have different kind of resources
        //as we have 5 Resources in our QMap we need to do this for each of those.

        QMapIterator<QString,uint> SourcesIterator(m_Planets[i]->getSources());
        while(SourcesIterator.hasNext())
        {
            SourcesIterator.next();
            for(int j=0; j<model->rowCount();j++)
            {
                if (model->headerData ( j, Qt::Vertical, Qt::DisplayRole)==SourcesIterator.key())
                {
                    index = model->index(j,i,QModelIndex()); //here we set the index for our source column and also the current row
                    model->setData(index,SourcesIterator.value());
                }
            }
        }
    }
    return model;
}

QStringList DataModel::getPIDataByPGrade(PIGrades grade)
{
    QStringList PINames;
    QList<PIProduct> PIProducts = m_PIData.getAll();
    for(int i=0;i<PIProducts.size();i++)
    {
        if(PIProducts[i].getPIGrade()==grade)
        {
            PINames.append(PIProducts[i].getPIName());
        }

    }
    return PINames;
}

void DataModel::getPIDataTreeItem(QTreeWidget* parent,PIProduct p)
{
    //this method is NOT recursive!

    //these constants are just for readabillity
    const int COLPRODUCTNAME =0;
    const int COLINPUTAMOUNT =1;
    const int COLOUTPUTAMOUNT =2;

    QTreeWidgetItem *Itemroot;
    Itemroot= new QTreeWidgetItem(parent);
    Itemroot->setText(COLPRODUCTNAME,p.getPIName());
    Itemroot->setText(COLINPUTAMOUNT,QString::number(p.getPIIngredientAmount()));
    Itemroot->setText(COLOUTPUTAMOUNT,QString::number(p.getPIQuantity()));

    if(p.getIngredient(1))
    {
        buildPIDataItemTree(Itemroot,p.getIngredient(1));

        if(p.getIngredient(2))
        {
            buildPIDataItemTree(Itemroot,p.getIngredient(2));

            if(p.getIngredient(3))
            {
                buildPIDataItemTree(Itemroot,p.getIngredient(3));
            }
        }
    }
}

QStringList DataModel::getPlanetTypes()
{
    QStringList PlanetTypesList;

    Planet p;
    const QMetaObject* metaObj = p.metaObject();
    QMetaEnum e = metaObj->enumerator(metaObj->indexOfEnumerator("PlanetTypes"));

    for(int i=0; i<e.keyCount();i++)
    {
        PlanetTypesList.append(e.key(i));
    }
    return PlanetTypesList;
    
}

QStringList DataModel::getBarrenSources()
{
    // no need to save a Planet as member for just getting the Sourcenames
    Planet p;
    return p.BarrenSources;
}

QStringList DataModel::getGasSources()
{
    Planet p;
    return p.GasSources;
}

QStringList DataModel::getIceSources()
{
    Planet p;
    return p.IceSources;
}

QStringList DataModel::getLavaSources()
{
    Planet p;
    return p.LavaSources;
}

QStringList DataModel::getOceanicSources()
{
    Planet p;
    return p.OceanicSources;
}

QStringList DataModel::getPlasmaSources()
{
    Planet p;
    return p.PlasmaSources;
}

QStringList DataModel::getStormSources()
{
    Planet p;
    return p.StromSources;
}

QStringList DataModel::getTemperateSources()
{
    Planet p;
    return p.TemperateSources;
}

QString DataModel::LastError()
{
    return m_Errors.last();
}

void DataModel::SavePlanet(QString name, QString systemname, QString type, QMap<QString, uint> sources)
{
    Planet p;
    p.setPlanetName(name);
    p.setSystemName(systemname);

    const QMetaObject* metaObj = p.metaObject();
    QMetaEnum e = metaObj->enumerator(metaObj->indexOfEnumerator("PlanetTypes"));

    //Quick conversion from QString to char* via QT FAQ
    QByteArray ba = type.toLocal8Bit();
    const char *ctype = ba.data();

    Planet::PlanetTypes PLType = static_cast<Planet::PlanetTypes>(e.keysToValue(ctype));

    p.setPlanetType(PLType);
    QMapIterator<QString,uint> SourcesIterator(sources);

    while(SourcesIterator.hasNext())
    {
        SourcesIterator.next();
        p.addSource(SourcesIterator.key(),SourcesIterator.value());
    }

    m_DbMan.savePlanet(p);
}

bool DataModel::LoadMaterialData()
{    
    //loads all the Material Data from the Database
    m_AbyssalMaterials = m_DbMan.LoadAbyssalMaterials();
    if(m_AbyssalMaterials.count()==0)
    {
        //then we have an Error occured.
        m_Errors.append(m_DbMan.LastError());
        return false;
    }
    m_Commodities = m_DbMan.LoadCommodities();
    if(m_Commodities.count()==0)
    {
        //then we have an Error occured.
        m_Errors.append(m_DbMan.LastError());
        return false;
    }
    m_FuelBlocks = m_DbMan.LoadFuelBlocks();
    if(m_FuelBlocks.count()==0)
    {
        //then we have an Error occured.
        m_Errors.append(m_DbMan.LastError());
        return false;
    }
    m_Gases = m_DbMan.LoadGases();
    if(m_Gases.count()==0)
    {
        //then we have an Error occured.
        m_Errors.append(m_DbMan.LastError());
        return false;
    }
    m_IceProducts = m_DbMan.LoadIceProducts();
    if(m_IceProducts.count()==0)
    {
        //then we have an Error occured.
        m_Errors.append(m_DbMan.LastError());
        return false;
    }
    m_Minerals = m_DbMan.LoadMinerals();
    if(m_Minerals.count()==0)
    {
        //then we have an Error occured.
        m_Errors.append(m_DbMan.LastError());
        return false;
    }
    m_MoonGoos = m_DbMan.LoadMoonGoos();
    if(m_MoonGoos.count()==0)
    {
        //then we have an Error occured.
        m_Errors.append(m_DbMan.LastError());
        return false;
    }
    m_NamedComponents = m_DbMan.LoadNamedComponents();
    if(m_NamedComponents.count()==0)
    {
        //then we have an Error occured.
        m_Errors.append(m_DbMan.LastError());
        return false;
    }
    m_ReactionMaterials = m_DbMan.LoadReactionMaterials();
    if(m_ReactionMaterials.count()==0)
    {
        //then we have an Error occured.
        m_Errors.append(m_DbMan.LastError());
        return false;
    }
    m_Salvages = m_DbMan.LoadSalvages();
    if(m_Salvages.count()==0)
    {
        //then we have an Error occured.
        m_Errors.append(m_DbMan.LastError());
        return false;
    }
    m_T1Products = m_DbMan.LoadT1Products();
    if(m_T1Products.count()==0)
    {
        //then we have an Error occured.
        m_Errors.append(m_DbMan.LastError());
        return false;
    }
    return true; //if we come until here everything is loaded well.
}

bool DataModel::LoadBlueprints()
{
    m_Blueprints = m_DbMan.LoadBlueprints();
    if(m_Blueprints.count()==0)
    {
        //then we have an Error occured.
        m_Errors.append(m_DbMan.LastError());
        return false;
    }
    return true; //loading ok
}

bool DataModel::LoadBlueprintMaterials()
{
    for(int i=0;i<m_Blueprints.count();i++)
    {
        if(!m_DbMan.LoadBlueprintMaterials(m_AbyssalMaterials,m_Commodities,m_FuelBlocks,m_Gases,m_IceProducts,m_Minerals,m_MoonGoos,m_NamedComponents,m_PIData,m_ReactionMaterials,m_Salvages,m_T1Products,m_Blueprints[i]))
        {
            //if an error occured
            m_Errors.append(m_DbMan.LastError());
            return false;
        }
    }

    return true;
}

QStringList DataModel::getBlueprintStringList()
{
    QStringList BlueprintStringList;

    for(int i=0; i<m_Blueprints.count();i++)
    {
        BlueprintStringList.append(m_Blueprints[i].BPName());
    }

    return BlueprintStringList;
}

Blueprint DataModel::getBlueprintByName(QString BpName)
{
    Blueprint blueprint;
    bool found =false;
    int i=0;
    while (!found && i<m_Blueprints.count())
    {
        if(m_Blueprints[i].BPName()==BpName)
        {
            blueprint = m_Blueprints[i];
            found =true;
        }
        i++;
    }
    return blueprint;
}

void DataModel::getBlueprintMaterialsTreeItem(QTreeWidget *parent, Blueprint bp)
{
    //these constants are just for readabillity
    const int COLPRODUCTNAME =0;
    const int COLINPUTAMOUNT =1;
    const int COLOUTPUTAMOUNT =2;

    QTreeWidgetItem *Itemroot;
    Itemroot= new QTreeWidgetItem(parent);
    Itemroot->setText(COLPRODUCTNAME,bp.BPProduct());
    Itemroot->setText(COLOUTPUTAMOUNT,QString::number(bp.BPAmount()));

    QList<Material> Mats = bp.Materials().values();
    for(int i=0;i<Mats.count();i++)
    {
        QTreeWidgetItem *child;
        child = new QTreeWidgetItem(Itemroot);
        child->setText(COLPRODUCTNAME,Mats[i].item.Name());
        child->setText(COLINPUTAMOUNT,QString::number(Mats[i].amount));
    }
}



QString DataModel::readPwdFile()
{
    //Load password from File pwd.txt - this is actual a simple solution to get progress.
    qint64 maxleng=64; //passwords longer than that are unusual i think
    QString filename="pwd.txt";
    QFile file(filename);
    file.open(QIODevice::ReadOnly);
    QTextStream in(&file);
    return in.readLine(maxleng);
}

QTreeWidgetItem *DataModel::buildPIDataItemTree(QTreeWidgetItem *parent, PIProduct *p)
{
    //This is a recursive Method!
    //the code here is not redundant because this data need to be filled for each child also

    //these constants are just for readabillity
    const int COLPRODUCTNAME =0;
    const int COLINPUTAMOUNT =1;
    const int COLOUTPUTAMOUNT =2;

    QTreeWidgetItem *child;
    child = new QTreeWidgetItem(parent);
    child->setText(COLPRODUCTNAME,p->getPIName());
    child->setText(COLINPUTAMOUNT,QString::number(p->getPIIngredientAmount()));
    child->setText(COLOUTPUTAMOUNT,QString::number(p->getPIQuantity()));

    if(p->getIngredient(1))
    {
        buildPIDataItemTree(child,p->getIngredient(1));

        if(p->getIngredient(2))
        {
            buildPIDataItemTree(child,p->getIngredient(2));

            if(p->getIngredient(3))
            {
                buildPIDataItemTree(child,p->getIngredient(3));
            }
            else
            {
                //Normaly you put your upwards code here
            }
        }
        else
        {
            //Normaly you put your upwards code here
        }
    }
    //if there is no first one there will be no other because of Database
    return child; //here we return from each layer of the tree
}
