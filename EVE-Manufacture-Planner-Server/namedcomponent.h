#ifndef NAMEDCOMPONENT_H
#define NAMEDCOMPONENT_H

#include <item.h>

class NamedComponent : public Item
{
public:
    NamedComponent();
    ~NamedComponent();

    int NCID() const;
    void setNCID(int newNCID);
    float NCSize() const;
    void setNCSize(float newNCSize);
    const QString &NCName() const;
    void setNCName(const QString &newNCName);
    const QString &NCGroup() const;
    void setNCGroup(const QString &newNCGroup);
};

#endif // NAMEDCOMPONENT_H
