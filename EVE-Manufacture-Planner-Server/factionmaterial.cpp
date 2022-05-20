#include "factionmaterial.h"

FactionMaterial::FactionMaterial()
{

}

int FactionMaterial::FMID() const
{
    return ItemId();
}

void FactionMaterial::setFMID(int newFMID)
{
    setItemId(newFMID);
}

float FactionMaterial::FMSize() const
{
    return Size();
}

void FactionMaterial::setFMSize(float newFMSize)
{
    setSize(newFMSize);
}

const QString &FactionMaterial::FMName() const
{
    return Name();
}

void FactionMaterial::setFMName(const QString &newFMName)
{
    setName(newFMName);
}
