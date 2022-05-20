#include "t2product.h"

T2Product::T2Product()
{

}

int T2Product::T2ID() const
{
    return ItemId();
}

void T2Product::setT2ID(int newT2ID)
{
    setItemId(newT2ID);
}

float T2Product::T2Size() const
{
    return Size();
}

void T2Product::setT2Size(float newT2Size)
{
    setSize(newT2Size);
}

const QString &T2Product::T2Name() const
{
    return Name();
}

void T2Product::setT2Name(const QString &newT2Name)
{
    setName(newT2Name);
}
