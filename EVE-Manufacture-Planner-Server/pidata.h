#ifndef PIDATA_H
#define PIDATA_H

#include "piproduct.h"
#include<QList>

class PIData
{
public:
    PIData();
    void Add(PIProduct p);
    PIProduct* getbyId(int piid);
    PIProduct getItem(int index);
    PIProduct getItemByName(QString name);
    QList<PIProduct>getAll();
private:
    QList<PIProduct> m_PIProducts;

};

#endif // PIDATA_H
