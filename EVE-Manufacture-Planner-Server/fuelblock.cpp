#include "fuelblock.h"

FuelBlock::FuelBlock()
{
    
}

FuelBlock::~FuelBlock()
{
    
}

int FuelBlock::FBID() const
{
    return ItemId();
}

void FuelBlock::setFBID(int newFBID)
{
    setItemId(newFBID);
}

float FuelBlock::FBSize() const
{
    return Size();
}

void FuelBlock::setFBSize(float newFBSize)
{
    setSize(newFBSize);
}

const QString &FuelBlock::FBName() const
{
    return Name();
}

void FuelBlock::setFBName(const QString &newFBName)
{
    setName(newFBName);
}

const QString &FuelBlock::FBGroup() const
{
    return ItemGroup();
}

void FuelBlock::setFBGroup(const QString &newFBGroup)
{
    setItemGroup(newFBGroup);
}

int FuelBlock::getFBBPID() const
{
    return FBBPID;
}

void FuelBlock::setFBBPID(int newFBBPID)
{
    FBBPID = newFBBPID;
}
