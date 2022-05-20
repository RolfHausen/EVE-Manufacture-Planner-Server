#include "salvage.h"

Salvage::Salvage()
{

}

int Salvage::getSALID() const
{
    return ItemId();
}

void Salvage::setSALID(int newSALID)
{
    setItemId(newSALID);
}

float Salvage::getSALSize() const
{
    return Size();
}

void Salvage::setSALSize(float newSALSize)
{
    setSize(newSALSize);
}

const QString &Salvage::getSALName() const
{
    return Name();
}

void Salvage::setSALName(const QString &newSALName)
{
    setName(newSALName);
}
