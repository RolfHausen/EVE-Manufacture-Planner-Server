#include "mineral.h"

Mineral::Mineral()
{

}

int Mineral::MinId() const
{
    return ItemId();
}

void Mineral::setMinId(int newMinId)
{
    setItemId(newMinId);
}

float Mineral::MinSize() const
{
    return Size();
}

void Mineral::setMinSize(float newMinSize)
{
    setSize(newMinSize);
}

const QString &Mineral::MinName() const
{
    return Name();
}

void Mineral::setMinName(const QString &newMinName)
{
    setName(newMinName);
}

const QString &Mineral::MinGroup() const
{
    return ItemGroup();
}

void Mineral::setMinGroup(const QString &newMinGroup)
{
    setItemGroup(newMinGroup);
}
