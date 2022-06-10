#include "gas.h"

Gas::Gas()
{

}

int Gas::GID() const
{
    return ItemId();
}

void Gas::setGID(int newGID)
{
    setItemId(newGID);
}

float Gas::GSize() const
{
    return Size();
}

void Gas::setGSize(float newGSize)
{
    setSize(newGSize);
}

const QString &Gas::GName() const
{
    return Name();
}

void Gas::setGName(const QString &newGName)
{
    setName(newGName);
}

const QString &Gas::GGroup() const
{
    return ItemGroup();
}

void Gas::setGGroup(const QString &newGGroup)
{
    setItemGroup(newGGroup);
}
