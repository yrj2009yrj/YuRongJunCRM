#ifndef CSELLER_H
#define CSELLER_H

#include "CPerson.h"

class CSeller final: public CPerson
{
public:
    CSeller();
    ~CSeller();

    float mfGetTotalSales() const;
    void mvSetTotalSales(float fTotalSales);

    float mfGetCommissionRate() const;
    void mvSetCommissionRate(float fCommissionRate);

    float mfGetSalary();
    QString msGetStr();

private:
    float mfTotalSales;
    float mfCommissionRate;
};

#endif // CSELLER_H
