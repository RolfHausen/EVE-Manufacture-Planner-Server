#include "namedcomponent.h"

NamedComponent::NamedComponent()
{
    
}

NamedComponent::~NamedComponent()
{
    
}

int NamedComponent::NCID() const
{
    return ItemId();
}

void NamedComponent::setNCID(int newNCID)
{
    setItemId(newNCID);
}

float NamedComponent::NCSize() const
{
    return Size();
}

void NamedComponent::setNCSize(float newNCSize)
{
    setSize(newNCSize);
}

const QString &NamedComponent::NCName() const
{
    return Name();
}

void NamedComponent::setNCName(const QString &newNCName)
{
    setName(newNCName);
}

const QString &NamedComponent::NCGroup() const
{
    return ItemGroup();
}

void NamedComponent::setNCGroup(const QString &newNCGroup)
{
    setItemGroup(newNCGroup);
}
