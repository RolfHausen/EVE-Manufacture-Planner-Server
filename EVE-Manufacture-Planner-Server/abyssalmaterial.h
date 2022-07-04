#ifndef ABYSSALMATERIAL_H
#define ABYSSALMATERIAL_H
#include<item.h>

class AbyssalMaterial: public Item
{
public:
    AbyssalMaterial();
    ~AbyssalMaterial();

    int AMID() const;
    void setAMID(int newAMID);
    float AMSize() const;
    void setAMSize(float newAMSize);
    const QString &AMName() const;
    void setAMName(const QString &newAMName);
    const QString &AMGroup() const;
    void setAMGroup(const QString &newAMGroup);   

};
#endif // ABYSSALMATERIAL_H
