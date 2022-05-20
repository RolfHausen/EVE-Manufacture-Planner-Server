#ifndef ICEPRODUCT_H
#define ICEPRODUCT_H

#include <item.h>

class IceProduct :Item
{
public:
    IceProduct();
    int IceID() const;
    void setIceID(int newIceID);
    float IceSize() const;
    void setIceSize(float newIceSize);
    const QString &IceName() const;
    void setIceName(const QString &newIceName);
};

#endif // ICEPRODUCT_H
