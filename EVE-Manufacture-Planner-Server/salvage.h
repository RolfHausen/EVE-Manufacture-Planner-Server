#ifndef SALVAGE_H
#define SALVAGE_H

#include<item.h>

class Salvage : public Item
{
public:
    Salvage();
    ~Salvage();

    int SALID() const;
    void setSALID(int newSALID);
    float SALSize() const;
    void setSALSize(float newSALSize);
    const QString &SALName() const;
    void setSALName(const QString &newSALName);

    const QString &SALGroup() const;
    void setSALGroup(const QString &newSALGroup);
};

#endif // SALVAGE_H
