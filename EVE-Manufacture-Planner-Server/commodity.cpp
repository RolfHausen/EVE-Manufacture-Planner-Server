#include "commodity.h"

Commodity::Commodity()
{

}

int Commodity::COID() const
{
    return ItemId();
}

void Commodity::setCOID(int newCOID)
{
    setItemId(newCOID);
}

float Commodity::getCOSize() const
{
    return Size();
}

void Commodity::setCOSize(float newCOSize)
{
    setSize(newCOSize);
}

const QString &Commodity::getCOName() const
{
    return Name();
}

void Commodity::setCOName(const QString &newCOName)
{
    setName(newCOName);
}

const QString &Commodity::getCOGroup() const
{
    return ItemGroup();
}

void Commodity::setCOGroup(const QString &newCOGroup)
{
    setItemGroup(newCOGroup);
}
