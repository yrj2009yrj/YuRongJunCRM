#include "CDirector.h"

CDirector::CDirector()
{
    msJobType = "Director";
    mfFixedSalary = 8000;
}

CDirector::~CDirector()
{

}

float CDirector::mfGetFixedSalary() const
{
    return mfFixedSalary;
}

void CDirector::mvSetFixedSalary(float fFixedSalary)
{
    mfFixedSalary = fFixedSalary;
}

float CDirector::mfGetSalary()
{
    mfSalary = mfFixedSalary;
    return mfSalary;
}

QString CDirector::msGetStr()
{
    return QString::number(miJobNumber) + ";" +
           msName + ";" +
           msDepartment + ";" +
           msJobType + ";" +
           QString::number(mfSalary) + ";" +
           "0" + ";" +
           "0";
}
