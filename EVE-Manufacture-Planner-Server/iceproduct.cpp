#include "iceproduct.h"

IceProduct::IceProduct()
{
    
}

IceProduct::~IceProduct()
{
    
}

int IceProduct::IceID() const
{
    return ItemId();
}

void IceProduct::setIceID(int newIceID)
{
    setItemId(newIceID);
}

float IceProduct::IceSize() const
{
    return Size();
}

void IceProduct::setIceSize(float newIceSize)
{
    setSize(newIceSize);
}

const QString &IceProduct::IceName() const
{
    return Name();
}

void IceProduct::setIceName(const QString &newIceName)
{
    setName(newIceName);
}

const QString &IceProduct::getIceGroup() const
{
    return ItemGroup();
}

void IceProduct::setIceGroup(const QString &newIceGroup)
{
    setItemGroup(newIceGroup);
}

int IceProduct::MatId() const
{
    return Item::MatId();
}

void IceProduct::setMatId(int newMatId)
{
    Item::setMatId(newMatId);
}
