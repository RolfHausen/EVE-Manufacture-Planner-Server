#include "salvage.h"

Salvage::Salvage()
{

}

int Salvage::SALID() const
{
    return ItemId();
}

void Salvage::setSALID(int newSALID)
{
    setItemId(newSALID);
}

float Salvage::SALSize() const
{
    return Size();
}

void Salvage::setSALSize(float newSALSize)
{
    setSize(newSALSize);
}

const QString &Salvage::SALName() const
{
    return Name();
}

void Salvage::setSALName(const QString &newSALName)
{
    setName(newSALName);
}

const QString &Salvage::SALGroup() const
{
    return ItemGroup();
}

void Salvage::setSALGroup(const QString &newSALGroup)
{
    setItemGroup(newSALGroup);
}
