#include "factionmaterial.h"

FactionMaterial::FactionMaterial()
{
    
}

FactionMaterial::~FactionMaterial()
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

const QString &FactionMaterial::FMGroup() const
{
    return ItemGroup();
}

void FactionMaterial::setFMGroup(const QString &newFMGroup)
{
    setItemGroup(newFMGroup);
}
