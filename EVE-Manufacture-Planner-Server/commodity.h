#ifndef COMMODITY_H
#define COMMODITY_H
#include <item.h>

class Commodity: public Item
{
public:
    Commodity();

    int COID() const;
    void setCOID(int newCOID);
    float getCOSize() const;
    void setCOSize(float newCOSize);
    const QString &getCOName() const;
    void setCOName(const QString &newCOName);
    const QString &getCOGroup() const;
    void setCOGroup(const QString &newCOGroup);  

};

#endif // COMMODITY_H
