#include "moongoo.h"

MoonGoo::MoonGoo()
{

}

int MoonGoo::getMGID() const
{
    return ItemId();
}

void MoonGoo::setMGID(int newMGID)
{
    setItemId(newMGID);
}

float MoonGoo::getMGSize() const
{
    return Size();
}

void MoonGoo::setMGSize(float newMGSize)
{
    setSize(newMGSize);
}

const QString &MoonGoo::getMGName() const
{
    return Name();
}

void MoonGoo::setMGName(const QString &newMGName)
{
    setName(newMGName);
}
