#ifndef CPERSON_H
#define CPERSON_H

#include <QString>


class CPerson
{
public:
    CPerson();
    virtual ~CPerson();

    unsigned int miGetJobNumber() const;
    void mvSetJobNumber(unsigned int iJobNumber);

    QString msGetName() const;
    void mvSetName(QString &sName);

    QString msGetDepartment() const;
    void mvSetDepartment(QString &sDepartment);

    QString msGetJobType() const;
    void mvSetJobType(QString &sJobType);

    virtual float mfGetSalary() = 0;
    virtual QString msGetStr() = 0;

protected:
    unsigned int miJobNumber;
    QString msName;
    QString msDepartment;
    QString msJobType;
    float mfSalary;
};

#endif // CPERSON_H
