#include "reactionmaterial.h"

ReactionMaterial::ReactionMaterial()
{
    
}

ReactionMaterial::~ReactionMaterial()
{
    
}

int ReactionMaterial::RMID() const
{
    return ItemId();
}

void ReactionMaterial::setRMID(int newRMID)
{
    setItemId(newRMID);
}

float ReactionMaterial::RMSize() const
{
    return Size();
}

void ReactionMaterial::setRMSize(float newRMSize)
{
    setSize(newRMSize);
}

const QString &ReactionMaterial::RMName() const
{
    return Name();
}

void ReactionMaterial::setRMName(const QString &newRMName)
{
    setName(newRMName);
}

const QString &ReactionMaterial::RMGroup() const
{
    return ItemGroup();
}

void ReactionMaterial::setRMGroup(const QString &newRMGroup)
{
    setItemGroup(newRMGroup);
}

int ReactionMaterial::getRMBPID() const
{
    return RMBPID;
}

void ReactionMaterial::setRMBPID(int newRMBPID)
{
    RMBPID = newRMBPID;
}
