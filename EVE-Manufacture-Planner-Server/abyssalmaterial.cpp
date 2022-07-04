#include "abyssalmaterial.h"

AbyssalMaterial::AbyssalMaterial()
{
    
}

AbyssalMaterial::~AbyssalMaterial()
{
    
}

int AbyssalMaterial::AMID() const
{
    return ItemId();
}

void AbyssalMaterial::setAMID(int newAMID)
{
    setItemId(newAMID);
}

float AbyssalMaterial::AMSize() const
{
    return Size();
}

void AbyssalMaterial::setAMSize(float newAMSize)
{
    setSize(newAMSize);
}

const QString &AbyssalMaterial::AMName() const
{
    return Name();
}

void AbyssalMaterial::setAMName(const QString &newAMName)
{
    setName(newAMName);
}

const QString &AbyssalMaterial::AMGroup() const
{
    return ItemGroup();
}

void AbyssalMaterial::setAMGroup(const QString &newAMGroup)
{
    setItemGroup(newAMGroup);
}
