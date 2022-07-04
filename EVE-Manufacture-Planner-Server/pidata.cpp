#include "pidata.h"

PIData::PIData()
{

}

void PIData::Add(PIProduct p)
{
    m_PIProducts.append(p);
}

PIProduct* PIData::getbyId(int piid)
{
    int i = 0;
    while (i < m_PIProducts.count())
    {
        if(m_PIProducts[i].getPIID()==piid)
        {
            PIProduct* product;
            product = &m_PIProducts[i];
            return product;
        }
        i++;
    }
    return nullptr;
}

PIProduct PIData::getItem(int index)
{
    return m_PIProducts[index];
}

PIProduct PIData::getItemByName(QString name)
{
    PIProduct product;
    bool found = false;
    int i = 0;
    while (!found)
    {
        if(m_PIProducts[i].getPIName()==name)
        {
            found=true;
            product=m_PIProducts[i];
        }
        i++;
    }
    return product;
}

QList<PIProduct> PIData::getAll()
{
    return m_PIProducts;
}


