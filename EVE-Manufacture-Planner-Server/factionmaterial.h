#ifndef FACTIONMATERIAL_H
#define FACTIONMATERIAL_H

#include <item.h>

class FactionMaterial :Item
{
public:
    FactionMaterial();

    int FMID() const;
    void setFMID(int newFMID);
    float FMSize() const;
    void setFMSize(float newFMSize);
    const QString &FMName() const;
    void setFMName(const QString &newFMName);
};

#endif // FACTIONMATERIAL_H
