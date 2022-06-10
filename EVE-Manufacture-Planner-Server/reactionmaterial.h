#ifndef REACTIONMATERIAL_H
#define REACTIONMATERIAL_H
#include <item.h>

class ReactionMaterial: public Item
{
public:
    ReactionMaterial();

    int RMID() const;
    void setRMID(int newRMID);
    float RMSize() const;
    void setRMSize(float newRMSize);
    const QString &RMName() const;
    void setRMName(const QString &newRMName);
    const QString &RMGroup() const;
    void setRMGroup(const QString &newRMGroup);

private:
    int m_RMID;
    float m_RMSize;
    QString m_RMName;
    QString m_RMGroup;
};

#endif // REACTIONMATERIAL_H
