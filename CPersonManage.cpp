#include "CPersonManage.h"
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include "CDirector.h"
#include "CTechnician.h"
#include "CSeller.h"
#include "CSalesManager.h"

#include <QDebug>

CPersonManage::CPersonManage():
    miNewestJobNumber(1000)
{
    mbReadAllPerson("person.db");
    mvPrintAllInfo();
}

CPersonManage::~CPersonManage()
{
    mbSaveAllPerson("person.db");
    QMap<unsigned int, CPerson *>::iterator i;
    for (i = mmAll.begin(); i != mmAll.end(); ++i) {
        delete i.value();
        i.value() = NULL;
        mmAll.remove(i.key());
    }
}

bool CPersonManage::mbAddDirector(float fFixedSalary, unsigned int iJobNumber, QString sName,
                                  QString sDepartment, bool bFlag)
{
    CDirector * op_person = new CDirector;
    if(op_person == NULL){
        return false;
    } else {
        op_person->mvSetFixedSalary(fFixedSalary);
        op_person->mvSetJobNumber(iJobNumber);
        op_person->mvSetName(sName);
        op_person->mvSetDepartment(sDepartment);
        mmAll.insert(iJobNumber, op_person);

        if (bFlag) {
            mvSetNewestJobNumber(iJobNumber);
        }
        return true;
    }
}

bool CPersonManage::mbAddTechnician(float fWorkTime, float fHourlyWage, unsigned int iJobNumber,
                                    QString sName, QString sDepartment, bool bFlag)
{
    CTechnician * op_person = new CTechnician;
    if(op_person == NULL){
        return false;
    } else {
        op_person->mvSetJobNumber(iJobNumber);
        op_person->mvSetName(sName);
        op_person->mvSetDepartment(sDepartment);
        op_person->mvSetWorkTime(fWorkTime);
        op_person->mvSetHourlyWage(fHourlyWage);
        mmAll.insert(iJobNumber, op_person);

        if (bFlag) {
            mvSetNewestJobNumber(iJobNumber);
        }
        return true;
    }
}

bool CPersonManage::mbAddSeller(float fTotalSales, float fCommissionRate, unsigned int iJobNumber,
                                QString sName, QString sDepartment, bool bFlag)
{
    CSeller * op_person = new CSeller;
    if(op_person == NULL){
        return false;
    } else {
        op_person->mvSetJobNumber(iJobNumber);
        op_person->mvSetName(sName);
        op_person->mvSetDepartment(sDepartment);
        op_person->mvSetTotalSales(fTotalSales);
        op_person->mvSetCommissionRate(fCommissionRate);
        mmAll.insert(iJobNumber, op_person);

        if (bFlag) {
            mvSetNewestJobNumber(iJobNumber);
        }
        return true;
    }
}

bool CPersonManage::mbAddSalesManager(float fBasicSalary, float fTotalSales, float fCommissionRate,
                                      unsigned int iJobNumber, QString sName, QString sDepartment, bool bFlag)
{
    CSalesManager * op_person = new CSalesManager;
    if(op_person == NULL){
        return false;
    } else {
        op_person->mvSetJobNumber(iJobNumber);
        op_person->mvSetName(sName);
        op_person->mvSetDepartment(sDepartment);
        op_person->mvSetBasicSalary(fBasicSalary);
        op_person->mvSetTotalSales(fTotalSales);
        op_person->mvSetCommissionRate(fCommissionRate);
        mmAll.insert(iJobNumber, op_person);

        if (bFlag) {
            mvSetNewestJobNumber(iJobNumber);
        }
        return true;
    }
}

void CPersonManage::mvAddPerson(QString str)
{
    QStringList slist = str.split(';');
    if (slist[3] == "Director") {
        mbAddDirector(slist[4].toFloat(), slist[0].toInt(), slist[1], slist[2]);
    } else if (slist[3] == "Technician") {
        mbAddTechnician(slist[4].toFloat(), slist[5].toFloat(),  slist[0].toInt(), slist[1], slist[2]);
    } else if (slist[3] == "Seller") {
        mbAddSeller(slist[4].toFloat(), slist[5].toFloat(),  slist[0].toInt(), slist[1], slist[2]);
    } else if (slist[3] == "SalesManager") {
        mbAddSalesManager(slist[4].toFloat(), slist[5].toFloat(), slist[6].toFloat(), slist[0].toInt(), slist[1], slist[2]);
    }
}

void CPersonManage::mvModifyPerson(QString sCurItem, QString str)
{
    CPerson* op_person = mpFindPerson(sCurItem.toInt());
    delete op_person;
    op_person = NULL;
    mmAll.remove(sCurItem.toInt());

    QStringList slist = str.split(';');
    if (slist[3] == "Director") {
        mbAddDirector(slist[4].toFloat(), slist[0].toInt(), slist[1], slist[2], false);
    } else if (slist[3] == "Technician") {
        mbAddTechnician(slist[4].toFloat(), slist[5].toFloat(),  slist[0].toInt(), slist[1], slist[2], false);
    } else if (slist[3] == "Seller") {
        mbAddSeller(slist[4].toFloat(), slist[5].toFloat(),  slist[0].toInt(), slist[1], slist[2], false);
    } else if (slist[3] == "SalesManager") {
        mbAddSalesManager(slist[4].toFloat(), slist[5].toFloat(), slist[6].toFloat(), slist[0].toInt(), slist[1], slist[2], false);
    }
}

CPerson* CPersonManage::mpFindPerson(unsigned int iJobNumber)
{
   return mmAll.find(iJobNumber).value();
}

void CPersonManage::mvDeletePerson(unsigned int iJobNumber)
{
    CPerson * op_person = mmAll.find(iJobNumber).value();
    delete op_person;
    mmAll.remove(iJobNumber);
}

void CPersonManage::mvPrintAllInfo()
{
    QMap<unsigned int, CPerson *>::const_iterator i;
    for (i = mmAll.constBegin(); i != mmAll.constEnd(); ++i) {
        qDebug() << i.key() << ":" << i.value()->miGetJobNumber() << "   " <<
                                      i.value()->msGetName() << "   " <<
                                      i.value()->msGetDepartment() << "   " <<
                                      i.value()->msGetJobType() << "   " <<
                                      i.value()->mfGetSalary();
    }
    qDebug() << miNewestJobNumber;
}

bool CPersonManage::mbReadAllPerson(QString sFileName)
{
    QSqlDatabase o_db = QSqlDatabase::addDatabase("QSQLITE");
    o_db.setDatabaseName(sFileName);
    if(o_db.open()) {
        qDebug()<<"Database Opened";

        QSqlQuery o_sql_query;
        QString s_select_all_sql = "select * from AllPerson";
        //查询所有记录
        o_sql_query.prepare(s_select_all_sql);
        if(!o_sql_query.exec()) {
            qDebug()<<o_sql_query.lastError();
            return false;
        } else {
            while(o_sql_query.next()) {
                QString s_tmp = o_sql_query.value(3).toString();
                if (s_tmp == "Director") {
                    mbAddDirector(o_sql_query.value(4).toFloat(), o_sql_query.value(0).toInt(),
                                  o_sql_query.value(1).toString(), o_sql_query.value(2).toString());
                } else if (s_tmp == "Technician") {
                    mbAddTechnician(o_sql_query.value(4).toFloat(), o_sql_query.value(5).toFloat(), o_sql_query.value(0).toInt(),
                                    o_sql_query.value(1).toString(), o_sql_query.value(2).toString());
                } else if (s_tmp == "Seller") {
                    mbAddSeller(o_sql_query.value(4).toFloat(), o_sql_query.value(5).toFloat(), o_sql_query.value(0).toInt(),
                                o_sql_query.value(1).toString(), o_sql_query.value(2).toString());
                } else if (s_tmp == "SalesManager") {
                    mbAddSalesManager(o_sql_query.value(4).toFloat(), o_sql_query.value(5).toFloat(), o_sql_query.value(6).toFloat(),
                                      o_sql_query.value(0).toInt(), o_sql_query.value(1).toString(), o_sql_query.value(2).toString());
                } else {
                    mvSetNewestJobNumber(o_sql_query.value(0).toInt());
                }
            }
            o_sql_query.exec(QString("delete from AllPerson where JobNumber = %1").arg(miNewestJobNumber));
       }
    } else {
        return false;
    }
    o_db.close();
    return true;
}

bool CPersonManage::mbSaveAllPerson(QString sFileName)
{
    QSqlDatabase o_db = QSqlDatabase::addDatabase("QSQLITE");
    o_db.setDatabaseName(sFileName);
    if(o_db.open()) {
        qDebug()<<"Database Opened";

        QSqlQuery o_sql_query;
        QString s_create_sql = "create table if not exists AllPerson (JobNumber int primary key,"
                                                                    "Name varchar(20),"
                                                                    "Department varchar(20),"
                                                                    "JobType varchar(20),"
                                                                    "Value1 float,"
                                                                    "Value2 float,"
                                                                    "Value3 float)";

        QString s_insert_sql = "insert into AllPerson values(%1,\"%2\",\"%3\",\"%4\",%5,%6,%7)";
        o_sql_query.prepare(s_create_sql); //创建表
        if(!o_sql_query.exec()) //查看创建表是否成功
        {
            qDebug()<<QObject::tr("Table Create failed");
            qDebug()<<o_sql_query.lastError();
        } else {
            qDebug()<< "Table Created" ;

            o_sql_query.exec("delete from AllPerson");

            QMap<unsigned int, CPerson *>::const_iterator i;
            for (i = mmAll.constBegin(); i != mmAll.constEnd(); ++i) {
                QString s_tmp = s_insert_sql;
                s_tmp = s_tmp.arg(i.value()->miGetJobNumber()).arg(i.value()->msGetName()).arg(i.value()->msGetDepartment()).arg(i.value()->msGetJobType());

                QString s_value = i.value()->msGetJobType();
                if (s_value == "Director") {
                    s_tmp.replace("%5",QString::number(static_cast<CDirector*>(i.value())->mfGetFixedSalary()));
                    s_tmp.replace("%6",QString("NULL"));
                    s_tmp.replace("%7",QString("NULL"));
                } else if (s_value == "Technician") {
                    s_tmp.replace("%5",QString::number(static_cast<CTechnician*>(i.value())->mfGetWorkTime()));
                    s_tmp.replace("%6",QString::number(static_cast<CTechnician*>(i.value())->mfGetHourlyWage()));
                    s_tmp.replace("%7",QString("NULL"));
                } else if (s_value == "Seller") {
                    s_tmp.replace("%5",QString::number(static_cast<CSeller*>(i.value())->mfGetTotalSales()));
                    s_tmp.replace("%6",QString::number(static_cast<CSeller*>(i.value())->mfGetCommissionRate()));
                    s_tmp.replace("%7",QString("NULL"));
                } else if (s_value == "SalesManager") {
                    s_tmp.replace("%5",QString::number(static_cast<CSalesManager*>(i.value())->mfGetBasicSalary()));
                    s_tmp.replace("%6",QString::number(static_cast<CSalesManager*>(i.value())->mfGetTotalSales()));
                    s_tmp.replace("%7",QString::number(static_cast<CSalesManager*>(i.value())->mfGetCommissionRate()));
                }

                o_sql_query.prepare(s_tmp);
                if(!o_sql_query.exec()) {
                    qDebug()<<o_sql_query.lastError();
                } else {
                    qDebug()<<"插入记录成功";
                }
            }
            o_sql_query.prepare("insert into AllPerson values(" + QString::number(miNewestJobNumber) + ",NULL,NULL,NULL,NULL,NULL,NULL)");
            if(!o_sql_query.exec()){
                qDebug()<<o_sql_query.lastError();
            } else {
                qDebug()<<"插入记录成功";
            }
            qDebug() << miNewestJobNumber;
        }
    } else {
           return false;
    }
    o_db.close();
    return true;
}

void CPersonManage::mvSetNewestJobNumber(unsigned int iNewestJobNumber)
{
    if (iNewestJobNumber > miNewestJobNumber) {
        miNewestJobNumber = iNewestJobNumber;
    } else {
        miNewestJobNumber++;
    }
}

QMap<unsigned int, CPerson *>* CPersonManage::mmGetAll()
{
    return &mmAll;
}

unsigned int CPersonManage::mvGetNewestJobNumber()
{
    return miNewestJobNumber;
}
