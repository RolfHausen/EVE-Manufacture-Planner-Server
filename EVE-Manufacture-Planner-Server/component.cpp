#include "component.h"

Component::Component()
{

}

int Component::COID() const
{
    return ItemId();
}

void Component::setCOID(int newCOID)
{
    setItemId(newCOID);
}

float Component::COSize() const
{
    return Size();
}

void Component::setCOSize(float newCOSize)
{
    setSize(newCOSize);
}

const QString &Component::COName() const
{
    return Name();
}

void Component::setCOName(const QString &newCOName)
{
    setName(newCOName);
}

int Component::getCOBPID() const
{
    return COBPID;
}

void Component::setCOBPID(int newCOBPID)
{
    COBPID = newCOBPID;
}
