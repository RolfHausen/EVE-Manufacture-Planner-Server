#ifndef ICEPRODUCT_H
#define ICEPRODUCT_H

#include <item.h>

class IceProduct: public Item
{
public:
    IceProduct();
    int IceID() const;
    void setIceID(int newIceID);
    float IceSize() const;
    void setIceSize(float newIceSize);
    const QString &IceName() const;
    void setIceName(const QString &newIceName);

    const QString &getIceGroup() const;
    void setIceGroup(const QString &newIceGroup);

    int MatId() const;
    void setMatId(int newMatId);

};

#endif // ICEPRODUCT_H
