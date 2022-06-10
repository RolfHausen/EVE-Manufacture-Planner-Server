#ifndef FUELBLOCK_H
#define FUELBLOCK_H
#include <item.h>

class FuelBlock:public Item
{
public:
    FuelBlock();

    int FBID() const;
    void setFBID(int newFBID);
    float FBSize() const;
    void setFBSize(float newFBSize);
    const QString &FBName() const;
    void setFBName(const QString &newFBName);
    const QString &FBGroup() const;
    void setFBGroup(const QString &newFBGroup);
};

#endif // FUELBLOCK_H
