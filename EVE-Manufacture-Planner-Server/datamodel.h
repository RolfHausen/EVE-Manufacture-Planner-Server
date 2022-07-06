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
    bool LoadMaterialData();
    bool LoadBlueprints();
    bool LoadBlueprintMaterials();

    QStringList getBlueprintStringList();    
    QStringList getProductStringList();    
    void getBlueprintMaterialsTreeItem(QTreeWidget* parent,Blueprint bp);

    const QList<Blueprint> &Blueprints() const;

private:
    DbManager m_DbMan;
    QStringList m_Errors;
    QString readPwdFile();
    PIData m_PIData;
    QList<Planet*> m_Planets; //? does this really need to be a List of Pointers?

    QList<AbyssalMaterial> m_AbyssalMaterials;
    QList<Commodity> m_Commodities;
    QList<FuelBlock> m_FuelBlocks;
    QList<Gas> m_Gases;
    QList<IceProduct> m_IceProducts;
    QList<Mineral> m_Minerals;
    QList<MoonGoo> m_MoonGoos;
    QList<NamedComponent> m_NamedComponents;
    QList<ReactionMaterial> m_ReactionMaterials;
    QList<Salvage> m_Salvages;
    QList<T1Product> m_T1Products;
    QList<Blueprint> m_Blueprints;

    void buildPIDataItemTree(QTreeWidgetItem* parent,PIProduct *p, int amount);
    void buildBlueprintItemTree(QTreeWidgetItem* parent, Blueprint bp, int amount);


};

#endif // DATAMODEL_H
