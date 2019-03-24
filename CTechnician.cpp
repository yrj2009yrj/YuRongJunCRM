#include "CTechnician.h"

CTechnician::CTechnician()
{
    msJobType = "Technician";
    mfHourlyWage = 100.0;
}

CTechnician::~CTechnician()
{

}

float CTechnician::mfGetWorkTime() const
{
    return mfWorkTime;
}

void CTechnician::mvSetWorkTime(float fWorkTime)
{
    mfWorkTime = fWorkTime;
}

float CTechnician::mfGetHourlyWage() const
{
    return mfHourlyWage;
}

void CTechnician::mvSetHourlyWage(float fHourlyWage)
{
    mfHourlyWage = fHourlyWage;
}

float CTechnician::mfGetSalary()
{
    mfSalary = mfWorkTime * mfHourlyWage;
    return mfSalary;
}

QString CTechnician::msGetStr()
{
    return QString::number(miJobNumber) + ";" +
           msName + ";" +
           msDepartment + ";" +
           msJobType + ";" +
           QString::number(mfWorkTime) + ";" +
           QString::number(mfHourlyWage) + ";" +
           "0";
}
