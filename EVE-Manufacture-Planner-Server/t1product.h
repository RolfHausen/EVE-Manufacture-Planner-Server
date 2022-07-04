#ifndef T1PRODUCT_H
#define T1PRODUCT_H

#include <item.h>

class T1Product : public Item
{
public:
    T1Product();
    ~T1Product();

    int T1ID() const;
    void setT1ID(int newT1ID);
    float T1Size() const;
    void setT1Size(float newT1Size);
    const QString &T1Name() const;
    void setT1Name(const QString &newT1Name);
    const QString &T1Group() const;
    void setT1Group(const QString &newT1Group);



    int getT1BPID() const;
    void setT1BPID(int newT1BPID);

private:
    int T1BPID;
};

#endif // T1PRODUCT_H
