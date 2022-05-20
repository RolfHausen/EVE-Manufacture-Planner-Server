#ifndef SALVAGE_H
#define SALVAGE_H

#include<item.h>

class Salvage : Item
{
public:
    Salvage();
    int getSALID() const;
    void setSALID(int newSALID);
    float getSALSize() const;
    void setSALSize(float newSALSize);
    const QString &getSALName() const;
    void setSALName(const QString &newSALName);
};

#endif // SALVAGE_H
