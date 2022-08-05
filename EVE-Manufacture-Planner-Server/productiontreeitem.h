#ifndef PRODUCTIONTREEITEM_H
#define PRODUCTIONTREEITEM_H
#include<QList>
#include<item.h>
#include<blueprint.h>

class ProductionTreeItem
{
public:
    ProductionTreeItem();

    //getter & setter
    const QList<ProductionTreeItem *> &TreeItems() const;
    void setTreeItems(const QList<ProductionTreeItem *> &newTreeItems);

    const QString &getItemtype() const;
    void setItemtype(const QString &newItemtype);
    Blueprint *ProductBlueprint() const;
    void setProductBlueprint(Blueprint *newProductBlueprint);
    int InputAmount() const;
    void setInputAmount(int newInputAmount);
    int OutputAmount() const;
    void setOutputAmount(int newOutputAmount);

    Item *Product() const;
    void setProduct(Item *newProduct);

    void AddProductionTreeItem(ProductionTreeItem* treeitem);

    bool hasBlueprint();

private:
    QList<ProductionTreeItem*> m_TreeItems;
    Item* m_Product;
    QString Itemtype;
    Blueprint* m_ProductBlueprint; //having a Blueprint is optional due to PIProducts does not depend on Blueprints
    int m_InputAmount;
    int m_OutputAmount;
};

#endif // PRODUCTIONTREEITEM_H
