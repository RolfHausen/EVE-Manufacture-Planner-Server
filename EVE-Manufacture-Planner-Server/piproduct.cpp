#include "piproduct.h"

PIProduct::PIProduct()
{
    m_PIIngredient_1=nullptr;
    m_PIIngredient_2=nullptr;
    m_PIIngredient_3=nullptr;
}

PIProduct::~PIProduct()
{
    
}

int PIProduct::getPIID()
{
    return ItemId(); //returns the Id from Item.
}

QString PIProduct::getPIName()
{
    return Name();
}

float PIProduct::getPISize()
{
    return Size();
}
///returns: the pointer of the PIProduct which is ingredient for the actual one and nullptr if none.
PIProduct *PIProduct::getIngredient(int index)
{
    switch (index)
    {
    case 1: return m_PIIngredient_1;
    case 2: return m_PIIngredient_2;
    case 3: return m_PIIngredient_3;
    default: throw "invalid getter index for getIngredient(int index)!";
    }
    return nullptr;
}

PIGrades PIProduct::getPIGrade()
{
    return m_PIGrade;
}

int PIProduct::getPIIngredientAmount()
{
    return m_PIIngredientAmount;
}

int PIProduct::getPIQuantity()
{
    return m_PIQuantity;
}

QString PIProduct::getPIFilename()
{
    return m_PIfilename;
}

QByteArray PIProduct::getPIFile()
{
    return m_PIFile;
}

void PIProduct::setPIID(int id)
{
    setItemId(id);
}

void PIProduct::setPIName(QString name)
{
    setName(name);
}

void PIProduct::setPiSize(float size)
{
    setSize(size);
}

void PIProduct::setIngredient(PIProduct *ingredient, int index)
{
    switch(index)
    {
    case 1: m_PIIngredient_1=ingredient; break;
    case 2: m_PIIngredient_2=ingredient; break;
    case 3: m_PIIngredient_3=ingredient; break;
    }

}

void PIProduct::setPIGrade(QString piGrade)
{
    if(piGrade=="P0") m_PIGrade=PIGrades::P0;
    else if(piGrade=="P1") m_PIGrade=PIGrades::P1;
    else if(piGrade=="P2") m_PIGrade=PIGrades::P2;
    else if(piGrade=="P3") m_PIGrade=PIGrades::P3;
    else if(piGrade=="P4") m_PIGrade=PIGrades::P4;
    else throw "Invalid PIGrade or Grade not available in Database!";
}

void PIProduct::setPIIngredientAmount(int amount)
{
    m_PIIngredientAmount=amount;
}

void PIProduct::setPIQuantity(int quantity)
{
    m_PIQuantity=quantity;
}

void PIProduct::setPIFile(QString filename, QByteArray file)
{
    m_PIfilename=filename;
    m_PIFile=file;
}

int PIProduct::multiplicator()
{
    int mult =0;
    switch(m_PIGrade)
    {
    case PIGrades::P0: mult = 8; break; //the p0 Mulitplicator is also 8 because the transformation from P0 to P1 is 1:1
    case PIGrades::P1: mult = 8; break;
    case PIGrades::P2: mult = 4; break;
    case PIGrades::P3: mult = 2; break;
    case PIGrades::P4: mult = 1; break;
    default: mult = 0; //this should never happen but just in case we set the multiplicator also to 0
    }
    return mult;
}
