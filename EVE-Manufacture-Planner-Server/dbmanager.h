#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <pidata.h>
#include <planet.h>
#include <blueprint.h>
#include <abyssalmaterial.h>
#include <commodity.h>
#include <fuelblock.h>
#include <gas.h>
#include <iceproduct.h>
#include <mineral.h>
#include <moongoo.h>
#include <namedcomponent.h>
#include <reactionmaterial.h>
#include <salvage.h>
#include <t1product.h>

#include <QSqlDatabase>
#include <QString>
#include <QSqlQuery>
#include <QDebug>
#include <QSqlError>
#include <QSqlRecord>
#include <QMapIterator>
#include <QList>

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
    int GetPlanetIDIfExists(Planet& p); //returns the ID if the Planet exists otherwise Zero.

    QList<AbyssalMaterial> LoadAbyssalMaterials();
    QList<Commodity> LoadCommodities();
    QList<FuelBlock> LoadFuelBlocks();
    QList<Gas> LoadGases();
    QList<IceProduct> LoadIceProducts();
    QList<Mineral> LoadMinerals();
    QList<MoonGoo> LoadMoonGoos();
    QList<NamedComponent> LoadNamedComponents();
    QList<ReactionMaterial> LoadReactionMaterials();
    QList<Salvage> LoadSalvages();
    QList<T1Product> LoadT1Products();
    QList<Blueprint> LoadBlueprints();

    bool LoadBlueprintMaterials(QList<AbyssalMaterial>& AbyssalMaterials,QList<Commodity>& Commodities,QList<FuelBlock>& FuelBlocks,QList<Gas>& Gases,QList<IceProduct>& IceProducts,QList<Mineral>& Minerals,QList<MoonGoo>& MoonGoos,QList<NamedComponent>& NamedComponents,PIData& Pdata,QList<ReactionMaterial>& ReactionMaterials,QList<Salvage>& Salvages,QList<T1Product>& T1Products,Blueprint& Blueprint);

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
