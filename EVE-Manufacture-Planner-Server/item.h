#ifndef ITEM_H
#define ITEM_H

#include <QString>

class Item
{
public:
    Item();
    virtual ~Item(){}
    Item(int id);
    int ItemId() const;
    void setItemId(int newItemId);

    const QString &Name() const;
    void setName(const QString &newName);

    float Size() const;
    void setSize(float newSize);

    const QString &ItemGroup() const;
    void setItemGroup(const QString &newItemGroup);

    int MatId() const;
    void setMatId(int newMatId);

private:
    int m_ItemId;
    QString m_Name;
    float m_Size;
    QString m_ItemGroup;
    int m_MatId; //this is the identificationnumber in the material-databasetable which is unique

};

#endif // ITEM_H
