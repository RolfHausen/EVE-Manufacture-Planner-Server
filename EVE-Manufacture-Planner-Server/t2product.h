#ifndef T2PRODUCT_H
#define T2PRODUCT_H


#include <item.h>

class T2Product : Item
{
public:
    T2Product();
    int T2ID() const;
    void setT2ID(int newT2ID);
    float T2Size() const;
    void setT2Size(float newT2Size);
    const QString &T2Name() const;
    void setT2Name(const QString &newT2Name);

};

#endif // T2PRODUCT_H
