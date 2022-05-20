#include "t3product.h"

T3Product::T3Product()
{

}

int T3Product::T3ID() const
{
    return ItemId();
}

void T3Product::setT3ID(int newT3ID)
{
    setItemId(newT3ID);
}

float T3Product::T3Size() const
{
    return Size();
}

void T3Product::setT3Size(float newT3Size)
{
    setSize(newT3Size);
}

const QString &T3Product::T3Name() const
{
    return Name();
}

void T3Product::setT3Name(const QString &newT3Name)
{
    setName(newT3Name);
}
