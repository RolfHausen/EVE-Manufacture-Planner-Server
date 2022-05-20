#ifndef MOONGOO_H
#define MOONGOO_H

#include<item.h>

class MoonGoo : Item
{
public:
    MoonGoo();
    int getMGID() const;
    void setMGID(int newMGID);
    float getMGSize() const;
    void setMGSize(float newMGSize);
    const QString &getMGName() const;
    void setMGName(const QString &newMGName);
};

#endif // MOONGOO_H
