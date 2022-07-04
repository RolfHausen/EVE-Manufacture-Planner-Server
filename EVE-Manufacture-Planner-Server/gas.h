#ifndef GAS_H
#define GAS_H

#include <item.h>

class Gas : public Item
{
public:
    Gas();
    ~Gas();

    int GID() const;
    void setGID(int newGID);
    float GSize() const;
    void setGSize(float newGSize);
    const QString &GName() const;
    void setGName(const QString &newGName);
    const QString &GGroup() const;
    void setGGroup(const QString &newGGroup);
};

#endif // GAS_H
