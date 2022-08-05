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

void DataModel::getPIDataTreeItem(QTreeWidget* parent,PIProduct p, int amount)
{
    //this method is NOT recursive!

    //these constants are just for readabillity
    const int COLPRODUCTNAME =0;
    const int COLINPUTAMOUNT =1;
    const int COLOUTPUTAMOUNT =2;

    QTreeWidgetItem *Itemroot;
    Itemroot= new QTreeWidgetItem(parent);
    Itemroot->setText(COLPRODUCTNAME,p.getPIName());    


    int inAmount = 0; //amount of Ingredients
    int outAmount = 0;
    int remains = 0; //restamount because of integer divison
    int quantity = p.getPIQuantity(); //outputmount per cycle
    int Prodcyle =0; //cycles to produce the requested amount

    if(amount>=quantity) //if amount is more than one cycle produces
    {
        Prodcyle = amount/quantity;
        remains = amount % quantity;
        if(remains > 0)
        {
           Prodcyle++; //we need to add one cycle
        }
        inAmount = Prodcyle * p.getPIIngredientAmount();
        outAmount = Prodcyle * quantity;
    }
    else //if the amount is smaller than one production cycle
    {
        inAmount = p.getPIIngredientAmount(); //then we produce exact one cylce
        outAmount = quantity;
    }

    Itemroot->setText(COLOUTPUTAMOUNT,QString::number(outAmount));

    if(p.getIngredient(1))
    {
        buildPIDataItemTree(Itemroot,p.getIngredient(1),inAmount);

        if(p.getIngredient(2))
        {
            buildPIDataItemTree(Itemroot,p.getIngredient(2),inAmount);

            if(p.getIngredient(3))
            {
                buildPIDataItemTree(Itemroot,p.getIngredient(3),inAmount);
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

QStringList DataModel::getProductStringList()
{
    QStringList ProductStringList;

    for(int i=0; i<m_Blueprints.count();i++)
    {
        ProductStringList.append(m_Blueprints[i].BPProduct());
    }

    QList<PIProduct> PiProducts = m_PIData.getAll();
    for(int i=0; i<PiProducts.count();i++)
    {
        ProductStringList.append(PiProducts[i].getPIName());
    }
    ProductStringList.sort(Qt::CaseSensitive);
    return ProductStringList;
}

//this creates only a ProductionTreeItem per Entry of Blueprints or PiProducts
//it does not create their materials / ingredients because this will be recursiv.
void DataModel::LoadProductionTrees()
{
    for(int i=0; i<m_Blueprints.count();i++)
    {
        ProductionTreeItem treeItem;        
        treeItem.setProductBlueprint(&m_Blueprints[i]);
        bool found = false;
        int j=0;

        if(m_Blueprints[i].BPType() == "Commodity")
        {
            while(!found && j < m_Commodities.count())
            {
                if(m_Commodities[j].getCOName() == m_Blueprints[i].BPProduct())
                {
                    found = true;
                    treeItem.setProduct(&m_Commodities[j]);
                }
                j++;
            }

        }
        else if(m_Blueprints[i].BPType() == "T1Product")
        {
            while(!found && j < m_T1Products.count())
            {
                if(m_T1Products[j].T1Name() == m_Blueprints[i].BPProduct())
                {
                    found = true;
                    treeItem.setProduct(&m_T1Products[j]);
                }
                j++;
            }
        }
        else if(m_Blueprints[i].BPType() == "Reaction")
        {
            while(!found && j < m_ReactionMaterials.count())
            {
                if(m_ReactionMaterials[j].RMName() == m_Blueprints[i].BPProduct())
                {
                    found = true;
                    treeItem.setProduct(&m_ReactionMaterials[j]);
                }
                j++;
            }
        }
        //this needs to be extended by every BPType that is inserted into Blueprint table

        treeItem.setItemtype(m_Blueprints[i].BPType());        
        //here we add it to our List.
        m_ProductionTrees.append(treeItem);
        buildProductionTrees(&treeItem);

    }

    QList<PIProduct> PiProducts = m_PIData.getAll();
    for(int i = 0; i < PiProducts.count(); i++)
    {
        ProductionTreeItem treeItem;
        treeItem.setProduct(&PiProducts[i]);
        treeItem.setItemtype("PIProduct");
        m_ProductionTrees.append(treeItem);
        buildProductionTrees(&treeItem);
    }
}

void DataModel::getBlueprintMaterialsTreeItem(QTreeWidget *parent, Blueprint bp, int amount)
{
    //this method is NOT recursive!

    //these constants are just for readabillity
    const int COLPRODUCTNAME =0;
    const int COLINPUTAMOUNT =1;
    const int COLOUTPUTAMOUNT =2;

    QTreeWidgetItem *Itemroot;
    Itemroot= new QTreeWidgetItem(parent);
    Itemroot->setText(COLPRODUCTNAME,bp.BPProduct());

    /* Explanation:
     * acutally we use the wanted production amount and not the runs
     * if we want to use the runs as directly input then the calculation is runs * bp.BPAmount
     * but here we go from the wanted production amount to the runs it would mean to produce the amount
     * even if that means we need to produce more then we need. For example 250 R.A.M. Starshiptech
     * can not be produced without overproduction as per run 100 pieces are made. so we have 3 runs
     * creating 300 pieces but thisway we have the 250 pieces and not just 200 and 50 missing or
     * realizing that our resource calculation is missing material for the other 50 pieces
     * meaning to start a third run
     */

    int ProdAmount = 0;    
    int remains = 0; //restamount because of integer divison
    int quantity = bp.BPAmount(); //outputmount per cycle
    int Prodcyle =0; //cycles to produce the requested amount

    if(amount>=bp.BPAmount())
    {
        Prodcyle = amount / quantity;
        remains = amount % quantity;
        if(remains>0)
        {
            Prodcyle++;
        }
        ProdAmount = Prodcyle * quantity;
    }
    else //if the amount is smaller than one run
    {
        ProdAmount= quantity;
    }

    Itemroot->setText(COLOUTPUTAMOUNT,QString::number(ProdAmount));

    buildBlueprintItemTree(Itemroot,bp,ProdAmount);

}


void DataModel::buildProductionTrees(ProductionTreeItem* parent)
{
    if(parent->hasBlueprint())
    {
        QList<Material> Mats = parent->ProductBlueprint()->Materials();

        for(int i=0; i<Mats.count();i++)
        {
            ProductionTreeItem* treeitem = new ProductionTreeItem();
            treeitem->setProduct(Mats[i].item);
            treeitem->setItemtype(Mats[i].itemtype);
            bool found = false;
            int j=0;
            while(!found && j < m_Blueprints.count())
            {
                if(m_Blueprints[j].BPProduct() == Mats[i].item->Name())
                {
                    found = true;
                    treeitem->setProductBlueprint(&m_Blueprints[j]);
                }
                j++;
            }
            parent->AddProductionTreeItem(treeitem);
            buildProductionTrees(treeitem);
        }
    }
    else if (parent->getItemtype()== "PIProduct")
    {
        PIProduct* p = dynamic_cast<PIProduct*>(parent->Product());
        for(int i=1; i<4; i++) //each PI can have 3 ingredients starting by index 1!
        {
            if(p->getIngredient(i)!= nullptr)
            {
                ProductionTreeItem* treeitem = new ProductionTreeItem();
                treeitem->setProduct(p->getIngredient(1));
                treeitem->setItemtype(parent->getItemtype()); //all ingedients of PI is also PI
                parent->AddProductionTreeItem(treeitem);
                buildProductionTrees(treeitem);
            }
        }
    }
    else //should be a Leaf of the Tree as it is a Mineral or something like this having no materials below
    {
       //in this case we do not need to add another child because it has no material below itself
       // and also itself is already be created in the recursive loop before.
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

const QList<ProductionTreeItem> &DataModel::ProductionTrees() const
{
    return m_ProductionTrees;
}

const QList<Blueprint> &DataModel::Blueprints() const
{
    return m_Blueprints;
}

void DataModel::buildPIDataItemTree(QTreeWidgetItem *parent, PIProduct *p, int amount)
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

    int inAmount = 0; //amount of Ingredients
    int remains = 0; //restamount because of integer divison
    int quantity = p->getPIQuantity(); //outputmount per cycle
    int Prodcyle =0; //cycles to produce the requested amount

    if(amount>=quantity) //if amount is more than one cycle produces
    {
        Prodcyle = amount/quantity;
        remains = amount % quantity;
        if(remains > 0)
        {
           Prodcyle++; //we need to add one cycle
        }
        inAmount = Prodcyle * p->getPIIngredientAmount();
    }
    else //if the amount is smaller than one production cycle
    {
        inAmount = p->getPIIngredientAmount(); //then we produce exact one cylce
    }


    //child->setText(COLOUTPUTAMOUNT,QString::number(outAmount));

    if(p->getIngredient(1))
    {
        buildPIDataItemTree(child,p->getIngredient(1),inAmount);

        if(p->getIngredient(2))
        {
            buildPIDataItemTree(child,p->getIngredient(2),inAmount);

            if(p->getIngredient(3))
            {
                buildPIDataItemTree(child,p->getIngredient(3),inAmount);
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
    else
    {
        inAmount = Prodcyle * p->getPIQuantity();
    }
    child->setText(COLINPUTAMOUNT,QString::number(inAmount));
    //because we build the tree up to down we do not need to return any value
}

void DataModel::buildBlueprintItemTree(QTreeWidgetItem *parent, Blueprint bp, int amount)
{
    //This is a recursive Method!
    //the code here is not redundant because this data need to be filled for each child also

    //these constants are just for readabillity
    const int COLPRODUCTNAME =0;
    const int COLINPUTAMOUNT =1;
    const int COLOUTPUTAMOUNT =2;

    QList<Material> Mats = bp.Materials();
    for(int i=0;i<Mats.count();i++)
    {
        QTreeWidgetItem *child;
        child = new QTreeWidgetItem(parent);
        child->setText(COLPRODUCTNAME,Mats[i].item->Name());

        int ProdAmount = 0;

        //now we need to determine what type our material is to consider if we need to add more nodes to our tree

        if(Mats[i].itemtype == "PIProduct")
        {
            //has a own architecture of ingrediens we can make use of.
            ProdAmount = Mats[i].amount * amount;
            PIProduct* p = dynamic_cast<PIProduct*>(Mats[i].item);            
            if(p->getIngredient(1)!=nullptr)
            {
                buildPIDataItemTree(child,p->getIngredient(1),ProdAmount);
            }
            if(p->getIngredient(2)!=nullptr)
            {
                buildPIDataItemTree(child,p->getIngredient(2),ProdAmount);
            }
            if(p->getIngredient(3)!=nullptr)
            {
                buildPIDataItemTree(child,p->getIngredient(3),ProdAmount);
            }


        }
        else if(Mats[i].itemtype == "Commodity")
        {
            Commodity* co = dynamic_cast<Commodity*>(Mats[i].item);
            bool found = false;
            int j=0;
            while(!found && j < m_Blueprints.count())
            {
                if(co->getCOBPID() == m_Blueprints[j].BPID())
                {
                    found = true;
                    int quantity = m_Blueprints[j].BPAmount();
                    int ProdCycle = 0;
                    int remains = 0;
                    int MatAmount = Mats[i].amount * amount;

                    if(MatAmount>=quantity)
                    {
                        ProdCycle = MatAmount / quantity;
                        remains = MatAmount % quantity;
                        if(remains > 0)
                        {
                            ProdCycle++;
                        }
                        ProdAmount = ProdCycle * quantity;
                    }
                    else // if the amount is smaller than one run
                    {
                        ProdAmount = quantity;
                    }


                    buildBlueprintItemTree(child,m_Blueprints[j],ProdAmount);
                }
                j++;
            }
            //if nothing is found then it simply has no Blueprint and therefor no materials and its tree is complete
        }

        else if(Mats[i].itemtype == "Reaction")
        {
            //get the corresponding ReactionFormula within the Blueprints
            ReactionMaterial* rm = dynamic_cast<ReactionMaterial*>(Mats[i].item);
            bool found = false;
            int j=0;
            while(!found && j < m_Blueprints.count())
            {
                if(rm->getRMBPID()==m_Blueprints[j].BPID())
                {
                    found=true;

                    int quantity = m_Blueprints[j].BPAmount();
                    int ProdCycle = 0;
                    int remains = 0;
                    int MatAmount = Mats[i].amount * amount;

                    if(MatAmount>=quantity)
                    {
                        ProdCycle = MatAmount / quantity;
                        remains = MatAmount % quantity;
                        if(remains > 0)
                        {
                            ProdCycle++;
                        }
                        ProdAmount = ProdCycle * quantity;
                    }
                    else // if the amount is smaller than one run
                    {
                        ProdAmount = quantity;
                    }

                    buildBlueprintItemTree(child,m_Blueprints[j],ProdAmount);
                }
                j++;
            }

        }
        else if(Mats[i].itemtype == "T1Product")
        {
            //check BlueprintId of the current Product
            T1Product* t1 = dynamic_cast<T1Product*>(Mats[i].item);
            bool found = false;
            int j=0;
            while (!found && j<m_Blueprints.count())
            {
               if(t1->getT1BPID()==m_Blueprints[j].BPID())
               {
                   found = true;

                   int quantity = m_Blueprints[j].BPAmount();
                   int ProdCycle = 0;
                   int remains = 0;
                   int MatAmount = Mats[i].amount * amount;

                   if(MatAmount>=quantity)
                   {
                       ProdCycle = MatAmount / quantity;
                       remains = MatAmount % quantity;
                       if(remains > 0)
                       {
                           ProdCycle++;
                       }
                       ProdAmount = ProdCycle * quantity;
                   }
                   else // if the amount is smaller than one run
                   {
                       ProdAmount = quantity;
                   }

                   buildBlueprintItemTree(child,m_Blueprints[j],ProdAmount);
               }
               j++;
            }
        }
        else if(Mats[i].itemtype == "FuelBlock")
        {
            //get the BlueprintId of the FuelBlock
            FuelBlock* fb= dynamic_cast<FuelBlock*>(Mats[i].item);
            bool found = false;
            int j =0;
            while(!found && j < m_Blueprints.count())
            {
                if(fb->getFBBPID()==m_Blueprints[j].BPID())
                {
                    found = true;

                    int quantity = m_Blueprints[j].BPAmount();
                    int ProdCycle = 0;
                    int remains = 0;
                    int MatAmount = Mats[i].amount * amount;

                    if(MatAmount>=quantity)
                    {
                        ProdCycle = MatAmount / quantity;
                        remains = MatAmount % quantity;
                        if(remains > 0)
                        {
                            ProdCycle++;
                        }
                        ProdAmount = ProdCycle * quantity;
                    }
                    else // if the amount is smaller than one run
                    {
                        ProdAmount = quantity;
                    }

                    buildBlueprintItemTree(child,m_Blueprints[j],ProdAmount);
                }
                j++;
            }
        }
        else
        {
            //all other Materials have no corresponding Blueprint or Material below
            ProdAmount = Mats[i].amount*amount;

        }
        child->setText(COLINPUTAMOUNT,QString::number(ProdAmount));

    }
}
