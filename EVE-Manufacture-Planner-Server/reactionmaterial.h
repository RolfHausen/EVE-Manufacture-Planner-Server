#ifndef REACTIONMATERIAL_H
#define REACTIONMATERIAL_H
#include <item.h>

class ReactionMaterial: public Item
{
public:
    ReactionMaterial();
    ~ReactionMaterial();

    int RMID() const;
    void setRMID(int newRMID);
    float RMSize() const;
    void setRMSize(float newRMSize);
    const QString &RMName() const;
    void setRMName(const QString &newRMName);
    const QString &RMGroup() const;
    void setRMGroup(const QString &newRMGroup);


    int getRMBPID() const;
    void setRMBPID(int newRMBPID);

private:
    int RMBPID;
};

#endif // REACTIONMATERIAL_H
