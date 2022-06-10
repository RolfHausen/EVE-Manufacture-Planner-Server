#include "item.h"

Item::Item()
{

}

Item::Item(int id)
{
    m_ItemId=id;
}

int Item::ItemId() const
{
    return m_ItemId;
}

void Item::setItemId(int newItemId)
{
    m_ItemId = newItemId;
}

const QString &Item::Name() const
{
    return m_Name;
}

void Item::setName(const QString &newName)
{
    m_Name = newName;
}

float Item::Size() const
{
    return m_Size;
}

void Item::setSize(float newSize)
{
    m_Size = newSize;
}

const QString &Item::ItemGroup() const
{
    return m_ItemGroup;
}

void Item::setItemGroup(const QString &newItemGroup)
{
    m_ItemGroup = newItemGroup;
}

int Item::MatId() const
{
    return m_MatId;
}

void Item::setMatId(int newMatId)
{
    m_MatId = newMatId;
}
