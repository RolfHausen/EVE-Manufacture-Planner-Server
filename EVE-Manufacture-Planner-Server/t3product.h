#ifndef T3PRODUCT_H
#define T3PRODUCT_H


#include <item.h>

class T3Product : public Item
{
public:
    T3Product();
    int T3ID() const;
    void setT3ID(int newT3ID);
    float T3Size() const;
    void setT3Size(float newT3Size);
    const QString &T3Name() const;
    void setT3Name(const QString &newT3Name);

};

#endif // T3PRODUCT_H
