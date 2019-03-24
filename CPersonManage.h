#ifndef CPERSONMANAGE_H
#define CPERSONMANAGE_H

#include "CPerson.h"
#include <QMap>

class CPersonManage
{
public:
    CPersonManage();
    ~CPersonManage();

    bool mbAddDirector(float fFixedSalary, unsigned int iJobNumber, QString sName, QString sDepartment, bool bFlag = true);
    bool mbAddTechnician(float fWorkTime, float fHourlyWage, unsigned int iJobNumber, QString sName, QString sDepartment, bool bFlag = true);
    bool mbAddSeller(float fTotalSales, float fCommissionRate, unsigned int iJobNumber, QString sName, QString sDepartment, bool bFlag = true);
    bool mbAddSalesManager(float fBasicSalary, float fTotalSales, float fCommissionRate, unsigned int iJobNumber, QString sName, QString sDepartment, bool bFlag = true);

    void mvAddPerson(QString str);
    void mvModifyPerson(QString sCurItem, QString str);

    CPerson* mpFindPerson(unsigned int iJobNumber);
    void mvDeletePerson(unsigned int iJobNumber);

    bool mbReadAllPerson(QString sFileName);
    bool mbSaveAllPerson(QString sFileName);

    void mvPrintAllInfo();

    unsigned int mvGetNewestJobNumber();
    void mvSetNewestJobNumber(unsigned int iNewestJobNumber);

    QMap<unsigned int, CPerson *>* mmGetAll();

private:
    QMap<unsigned int, CPerson *> mmAll;
    unsigned int miNewestJobNumber;

    CPersonManage(const CPersonManage&);
    CPersonManage& operator=(const CPersonManage&);
};

#endif // CPERSONMANAGE_H
