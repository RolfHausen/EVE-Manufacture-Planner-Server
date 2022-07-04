#ifndef MOONGOO_H
#define MOONGOO_H

#include<item.h>

class MoonGoo : public Item
{
public:
    MoonGoo();
    ~MoonGoo();

    int MGID() const;
    void setMGID(int newMGID);
    float MGSize() const;
    void setMGSize(float newMGSize);
    const QString &MGName() const;
    void setMGName(const QString &newMGName);
    const QString &MGGroup() const;
    void setMGGroup(const QString &newMGGroup);

};

#endif // MOONGOO_H
