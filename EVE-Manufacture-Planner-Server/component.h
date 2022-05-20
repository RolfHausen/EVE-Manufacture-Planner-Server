#ifndef COMPONENT_H
#define COMPONENT_H

#include<item.h>

class Component : Item
{
public:
    Component();
    int COID() const;
    void setCOID(int newCOID);
    float COSize() const;
    void setCOSize(float newCOSize);
    const QString &COName() const;
    void setCOName(const QString &newCOName);
    int getCOBPID() const;
    void setCOBPID(int newCOBPID);

private:
    int COBPID; //the BlueprintID of the referred Blueprint to build this Component!
    //Attention this refers to the unresearched BP in the first place!
};

#endif // COMPONENT_H
