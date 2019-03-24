#ifndef CTECHNICIAN_H
#define CTECHNICIAN_H

#include "CPerson.h"

class CTechnician final: public CPerson
{
public:
    CTechnician();
    ~CTechnician();

    float mfGetWorkTime() const;
    void mvSetWorkTime(float fWorkTime);

    float mfGetHourlyWage() const;
    void mvSetHourlyWage(float fHourlyWage);

    float mfGetSalary();
    QString msGetStr();

private:
    float mfWorkTime;
    float mfHourlyWage;
};

#endif // CTECHNICIAN_H
