#ifndef BLUEPRINT_H
#define BLUEPRINT_H
#include<item.h>
#include<QMap>

struct Material
{
    int amount;
    Item item;
};

class Blueprint: public Item
{
public:
    Blueprint();

    int BPID() const;
    void setBPID(int newBPID);
    float BPSize() const;
    void setBPSize(float newBPSize);
    const QString &BPName() const;
    void setBPName(const QString &newBPName);
    const QString &BPGroup() const;
    void setBPGroup(const QString &newBPGroup);
    const QString &BPProduct() const;
    void setBPProduct(const QString &newBPProduct);
    int BPAmount() const;
    void setBPAmount(int newBPAmount);
    const QString &BPType() const;
    void setBPType(const QString &newBPType);
    const QMap<int, Material> &Materials() const;

    void AddMaterial(int matid,Material mat);

private:

    QString m_BPProduct;
    int m_BPAmount; // this is the quantity that will be produced from the blueprint as output
    QString m_BPType;
    QMap<int,Material> m_Materials; //maps the MATID as the key and the refered material

};

#endif // BLUEPRINT_H
