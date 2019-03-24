#ifndef CDIRECTOR_H
#define CDIRECTOR_H

#include "CPerson.h"

class CDirector final: public CPerson
{
public:
    CDirector();
    ~CDirector();

    float mfGetFixedSalary() const;
    void mvSetFixedSalary(float fFixedSalary);

    float mfGetSalary();
    QString msGetStr();

private:
    float mfFixedSalary;
};

#endif // CDIRECTOR_H
