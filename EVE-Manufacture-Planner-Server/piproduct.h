#ifndef PIPRODUCT_H
#define PIPRODUCT_H

#include<QString>
#include<item.h>


enum PIGrades
{
    P0,
    P1,
    P2,
    P3,
    P4
};

class PIProduct : public Item
{
public:
    PIProduct();
    ~PIProduct();

    //Getters
    int getPIID();
    QString getPIName();
    float getPISize();
    PIProduct* getIngredient(int index);
    PIGrades getPIGrade();
    int getPIIngredientAmount();
    int getPIQuantity();
    QString getPIFilename();
    QByteArray getPIFile();

    //Setters
    void setPIID(int id);
    void setPIName(QString name);
    void setPiSize(float size);    
    void setIngredient(PIProduct* ingredient,int index);
    void setPIGrade(QString piGrade);
    void setPIIngredientAmount(int amount);
    void setPIQuantity(int quantity);
    void setPIFile(QString filename, QByteArray file);

    int multiplicator(); //this method return a multiplicator depending on the PIGrade

private:    
    //size of the item, needed for transport calculation later
    PIProduct* m_PIIngredient_1; //ingredients needed for producing this product
    PIProduct* m_PIIngredient_2; //those can be null if there is nothing needed
    PIProduct* m_PIIngredient_3;
    PIGrades m_PIGrade; //refers to PIPx column at DB
    int m_PIIngredientAmount; //is the amount of pieces from each Ingredient
    int m_PIQuantity; //is the output amount when this is produced
    QString m_PIfilename; //is the filename
    QByteArray m_PIFile; //is the filedata
};


#endif // PIPRODUCT_H
