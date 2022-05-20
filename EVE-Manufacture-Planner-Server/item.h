#ifndef ITEM_H
#define ITEM_H

#include <QString>

class Item
{
public:
    Item();
    Item(int id);
    int ItemId() const;
    void setItemId(int newItemId);

    const QString &Name() const;
    void setName(const QString &newName);

    float Size() const;
    void setSize(float newSize);

private:
    int m_itemId;
    QString m_Name;
    float m_Size;

};

#endif // ITEM_H
