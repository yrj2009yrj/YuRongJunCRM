#include "CSeller.h"

CSeller::CSeller()
{
    msJobType = "Seller";
    mfCommissionRate = 0.04;
}

CSeller::~CSeller()
{

}

float CSeller::mfGetTotalSales() const
{
    return mfTotalSales;
}

void CSeller::mvSetTotalSales(float fTotalSales)
{
    mfTotalSales = fTotalSales;
}

float CSeller::mfGetCommissionRate() const
{
    return mfCommissionRate;
}

void CSeller::mvSetCommissionRate(float fCommissionRate)
{
    mfCommissionRate = fCommissionRate;
}

float CSeller::mfGetSalary()
{
    mfSalary = mfTotalSales * mfCommissionRate;
    return mfSalary;
}

QString CSeller::msGetStr()
{
    return QString::number(miJobNumber) + ";" +
           msName + ";" +
           msDepartment + ";" +
           msJobType + ";" +
           QString::number(mfTotalSales) + ";" +
           QString::number(mfCommissionRate) + ";" +
           "0";
}
