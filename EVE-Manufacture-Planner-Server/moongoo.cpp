#include "moongoo.h"

MoonGoo::MoonGoo()
{

}

int MoonGoo::MGID() const
{
    return ItemId();
}

void MoonGoo::setMGID(int newMGID)
{
    setItemId(newMGID);
}

float MoonGoo::MGSize() const
{
    return Size();
}

void MoonGoo::setMGSize(float newMGSize)
{
    setSize(newMGSize);
}

const QString &MoonGoo::MGName() const
{
    return Name();
}

void MoonGoo::setMGName(const QString &newMGName)
{
    setName(newMGName);
}

const QString &MoonGoo::MGGroup() const
{
    return ItemGroup();
}

void MoonGoo::setMGGroup(const QString &newMGGroup)
{
    setItemGroup(newMGGroup);
}


