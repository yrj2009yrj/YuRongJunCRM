#include "CSalesManager.h"

CSalesManager::CSalesManager()
{
    msJobType = "SalesManager";
    mfBasicSalary = 5000;
    mfCommissionRate = 0.005;
}

CSalesManager::~CSalesManager()
{

}

float CSalesManager::mfGetBasicSalary() const
{
    return mfBasicSalary;
}

void CSalesManager::mvSetBasicSalary(float fBasicSalary)
{
    mfBasicSalary = fBasicSalary;
}

float CSalesManager::mfGetTotalSales() const
{
    return mfTotalSales;
}

void CSalesManager::mvSetTotalSales(float fTotalSales)
{
    mfTotalSales = fTotalSales;
}

float CSalesManager::mfGetCommissionRate() const
{
    return mfCommissionRate;
}

void CSalesManager::mvSetCommissionRate(float fCommissionRate)
{
    mfCommissionRate = fCommissionRate;
}

float CSalesManager::mfGetSalary()
{
    mfSalary = mfBasicSalary + mfTotalSales * mfCommissionRate;
    return mfSalary;
}

QString CSalesManager::msGetStr()
{
    return QString::number(miJobNumber) + ";" +
           msName + ";" +
           msDepartment + ";" +
           msJobType + ";" +
           QString::number(mfBasicSalary) + ";" +
           QString::number(mfTotalSales) + ";" +
           QString::number(mfCommissionRate);
}
