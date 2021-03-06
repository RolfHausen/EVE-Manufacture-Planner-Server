#include "t1product.h"

T1Product::T1Product()
{
    
}

T1Product::~T1Product()
{
    
}

int T1Product::T1ID() const
{
    return ItemId();
}

void T1Product::setT1ID(int newT1ID)
{
    setItemId(newT1ID);
}

float T1Product::T1Size() const
{
    return Size();
}

void T1Product::setT1Size(float newT1Size)
{
    setSize(newT1Size);
}

const QString &T1Product::T1Name() const
{
    return Name();
}

void T1Product::setT1Name(const QString &newT1Name)
{
    setName(newT1Name);
}

const QString &T1Product::T1Group() const
{
    return ItemGroup();
}

void T1Product::setT1Group(const QString &newT1Group)
{
    setItemGroup(newT1Group);
}

int T1Product::getT1BPID() const
{
    return T1BPID;
}

void T1Product::setT1BPID(int newT1BPID)
{
    T1BPID = newT1BPID;
}
