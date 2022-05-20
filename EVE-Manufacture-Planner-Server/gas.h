#ifndef GAS_H
#define GAS_H

#include <item.h>

class Gas : Item
{
public:
    Gas();
    int GID() const;
    void setGID(int newGID);
    float GSize() const;
    void setGSize(float newGSize);
    const QString &GName() const;
    void setGName(const QString &newGName);

};

#endif // GAS_H
