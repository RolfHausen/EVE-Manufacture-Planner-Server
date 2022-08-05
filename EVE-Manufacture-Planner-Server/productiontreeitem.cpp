#include "productiontreeitem.h"

ProductionTreeItem::ProductionTreeItem()
{
    //to avoid dangling pointer
    m_Product = nullptr;
    m_ProductBlueprint = nullptr;
}

const QList<ProductionTreeItem *> &ProductionTreeItem::TreeItems() const
{
    return m_TreeItems;
}

void ProductionTreeItem::setTreeItems(const QList<ProductionTreeItem *> &newTreeItems)
{
    m_TreeItems = newTreeItems;
}

Item *ProductionTreeItem::Product() const
{
    return m_Product;
}

void ProductionTreeItem::setProduct(Item *newProduct)
{
    m_Product = newProduct;
}

void ProductionTreeItem::AddProductionTreeItem(ProductionTreeItem *treeitem)
{
    m_TreeItems.append(treeitem);
}

bool ProductionTreeItem::hasBlueprint()
{
    return m_ProductBlueprint != nullptr;
}

const QString &ProductionTreeItem::getItemtype() const
{
    return Itemtype;
}

void ProductionTreeItem::setItemtype(const QString &newItemtype)
{
    Itemtype = newItemtype;
}

Blueprint *ProductionTreeItem::ProductBlueprint() const
{
    return m_ProductBlueprint;
}

void ProductionTreeItem::setProductBlueprint(Blueprint *newProductBlueprint)
{
    m_ProductBlueprint = newProductBlueprint;
}

int ProductionTreeItem::InputAmount() const
{
    return m_InputAmount;
}

void ProductionTreeItem::setInputAmount(int newInputAmount)
{
    m_InputAmount = newInputAmount;
}

int ProductionTreeItem::OutputAmount() const
{
    return m_OutputAmount;
}

void ProductionTreeItem::setOutputAmount(int newOutputAmount)
{
    m_OutputAmount = newOutputAmount;
}
