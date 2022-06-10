#ifndef FACTIONMATERIAL_H
#define FACTIONMATERIAL_H

#include <item.h>

class FactionMaterial :public Item
{
public:
    FactionMaterial();

    int FMID() const;
    void setFMID(int newFMID);
    float FMSize() const;
    void setFMSize(float newFMSize);
    const QString &FMName() const;
    void setFMName(const QString &newFMName);

    const QString &FMGroup() const;
    void setFMGroup(const QString &newFMGroup);    
};

#endif // FACTIONMATERIAL_H
