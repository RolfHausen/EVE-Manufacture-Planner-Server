#include "blueprint.h"

Blueprint::Blueprint()
{

}

int Blueprint::BPID() const
{
    return ItemId();
}

void Blueprint::setBPID(int newBPID)
{
    setItemId(newBPID);
}

float Blueprint::BPSize() const
{
    return Size();
}

void Blueprint::setBPSize(float newBPSize)
{
    setSize(newBPSize);
}

const QString &Blueprint::BPName() const
{
    return Name();
}

void Blueprint::setBPName(const QString &newBPName)
{
    setName(newBPName);
}

const QString &Blueprint::BPGroup() const
{
    return ItemGroup();
}

void Blueprint::setBPGroup(const QString &newBPGroup)
{
    setItemGroup(newBPGroup);
}

const QString &Blueprint::BPProduct() const
{
    return m_BPProduct;
}

void Blueprint::setBPProduct(const QString &newBPProduct)
{
    m_BPProduct = newBPProduct;
}

int Blueprint::BPAmount() const
{
    return m_BPAmount;
}

void Blueprint::setBPAmount(int newBPAmount)
{
    m_BPAmount = newBPAmount;
}

const QString &Blueprint::BPType() const
{
    return m_BPType;
}

void Blueprint::setBPType(const QString &newBPType)
{
    m_BPType = newBPType;
}

const QMap<int, Material> &Blueprint::Materials() const
{
    return m_Materials;
}

void Blueprint::AddMaterial(int matid, Material mat)
{
    m_Materials.insert(matid,mat);
}
