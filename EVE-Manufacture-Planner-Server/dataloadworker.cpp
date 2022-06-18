#include "dataloadworker.h"
#include <globals.h>

DataLoadWorker::DataLoadWorker()
{

}

DataLoadWorker::~DataLoadWorker()
{

}

void DataLoadWorker::process()
{
    m_DM.openDb();
    m_DM.LoadPIData();
    m_DM.LoadBlueprints(); //loads all Blueprints from Db
    m_DM.LoadMaterialData(); //loads all Materials from Db
    m_DM.LoadBlueprintMaterials(); //loads the needed Materials for each Blueprint

    emit deployData(m_DM);
    emit finished();
}
