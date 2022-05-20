#ifndef NAMEDCOMPONENT_H
#define NAMEDCOMPONENT_H

#include <item.h>

class NamedComponent : Item
{
public:
    NamedComponent();
    int NCID() const;
    void setNCID(int newNCID);
    float NCSize() const;
    void setNCSize(float newNCSize);
    const QString &NCName() const;
    void setNCName(const QString &newNCName);
};

#endif // NAMEDCOMPONENT_H
