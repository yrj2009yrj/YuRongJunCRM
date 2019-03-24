#ifndef CSALESMANAGER_H
#define CSALESMANAGER_H

#include "CPerson.h"

class CSalesManager final: public CPerson
{
public:
    CSalesManager();
    ~CSalesManager();

    float mfGetBasicSalary() const;
    void mvSetBasicSalary(float fBasicSalary);

    float mfGetTotalSales() const;
    void mvSetTotalSales(float fTotalSales);

    float mfGetCommissionRate() const;
    void mvSetCommissionRate(float fCommissionRate);

    float mfGetSalary();
    QString msGetStr();

private:
    float mfBasicSalary;
    float mfTotalSales;
    float mfCommissionRate;
};

#endif // CSALESMANAGER_H
