#include "CPerson.h"

CPerson::CPerson():
    miJobNumber(0),msName(""),msDepartment(""),
    msJobType(""),mfSalary(0.0)
{

}

CPerson::~CPerson()
{

}

unsigned int CPerson::miGetJobNumber() const
{
    return miJobNumber;
}

void CPerson::mvSetJobNumber(unsigned int iJobNumber)
{
    miJobNumber = iJobNumber;
}

QString CPerson::msGetName() const
{
    return msName;
}

void CPerson::mvSetName(QString &sName)
{
    msName = sName;
}

QString CPerson::msGetDepartment() const
{
    return msDepartment;
}

void CPerson::mvSetDepartment(QString &sDepartment)
{
    msDepartment = sDepartment;
}

QString CPerson::msGetJobType() const
{
    return msJobType;
}

void CPerson::mvSetJobType(QString &sJobType)
{
    msJobType = sJobType;
}
