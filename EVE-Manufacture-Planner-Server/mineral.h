#ifndef MINERAL_H
#define MINERAL_H
#include<item.h>

class Mineral : Item
{
    //this particular class seems to not make sense in the first look
    //but this is needed to store all types of items in the inventory later
    //otherwise it would be needed to store the different types of materials in different containers
    //which would then restict the options at the ui later also.

    //so for the moment this class uses just only the attributes and methods of its superclass

public:
    Mineral();
    int MinId() const;
    void setMinId(int newMinId);
    float MinSize() const;
    void setMinSize(float newMinSize);

    const QString &MinName() const;
    void setMinName(const QString &newMinName);






};

#endif // MINERAL_H
