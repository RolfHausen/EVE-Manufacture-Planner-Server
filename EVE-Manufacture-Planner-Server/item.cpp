#include "item.h"

Item::Item()
{

}

Item::Item(int id)
{
    m_itemId=id;
}

int Item::ItemId() const
{
    return m_itemId;
}

void Item::setItemId(int newItemId)
{
    m_itemId = newItemId;
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
