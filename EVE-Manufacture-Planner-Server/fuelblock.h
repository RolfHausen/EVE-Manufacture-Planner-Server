#ifndef FUELBLOCK_H
#define FUELBLOCK_H
#include <item.h>

class FuelBlock:public Item
{
public:
    FuelBlock();
    ~FuelBlock();

    int FBID() const;
    void setFBID(int newFBID);
    float FBSize() const;
    void setFBSize(float newFBSize);
    const QString &FBName() const;
    void setFBName(const QString &newFBName);
    const QString &FBGroup() const;
    void setFBGroup(const QString &newFBGroup);

    int getFBBPID() const;
    void setFBBPID(int newFBBPID);

private:
    int FBBPID;
};

#endif // FUELBLOCK_H
