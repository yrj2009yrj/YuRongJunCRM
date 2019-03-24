#include "CMainWin.h"
#include "CInfoDia.h"

#include <QDebug>

CMainWin::CMainWin(QWidget *parent) :
    QMainWindow(parent)
{
    setupUi();

    mAll = moPersonManage.mmGetAll();

    connect(mopbtnAdd, SIGNAL(clicked()), this, SLOT(msltAddClicked()));
    connect(mopbtnModify, SIGNAL(clicked()), this, SLOT(msltModifyClicked()));
    connect(mopbtnDelete, SIGNAL(clicked()), this, SLOT(msltDeleteClicked()));
    connect(mopListWidget, SIGNAL(currentTextChanged(QString)), this , SLOT(msltShowPerson(QString)));

    mvUpdateListWidget();
    mopListWidget->setCurrentRow(0);

    connect(mopWidTab, SIGNAL(currentChanged(int)), this, SLOT(msltWidChanged(int)));
    mopWidTab->setCurrentIndex(0);

    connect(mopcbxCondition, SIGNAL(currentIndexChanged(QString)), this, SLOT(msltCbxChanged(QString)));
    connect(mopbtnSearch, SIGNAL(clicked()), this, SLOT(msltSearchClicked()));

    msJobCondition = "All";
}

CMainWin::~CMainWin()
{
}

void CMainWin::msltAddClicked()
{
    QString str = "add;";
    str += QString::number(moPersonManage.mvGetNewestJobNumber()) + ";;;;;;";
    CInfoDia mo_info_dia(&str);

    if (mo_info_dia.exec() == QDialog::Accepted) {
        moPersonManage.mvAddPerson(str);
    } else {
        qDebug() << str;
    }
    mvUpdateListWidget();
}

void CMainWin::msltModifyClicked()
{
    //modify
    QString str = "modify;";
    CPerson * op_person = moPersonManage.mpFindPerson(msCurItem.toInt());
    str += op_person->msGetStr();

//    qDebug() << str;
    CInfoDia mo_info_dia(&str);

    if (mo_info_dia.exec() == QDialog::Accepted) {
        moPersonManage.mvModifyPerson(msCurItem, str);
    } else {
        qDebug() << str;
    }
    mvUpdateListWidget();
}

void CMainWin::msltDeleteClicked()
{
    moPersonManage.mvDeletePerson(msCurItem.toInt());
    mvUpdateListWidget();
}

void CMainWin::mvUpdateListWidget()
{
    int i_cur_row = mopListWidget->currentRow();
    disconnect(mopListWidget, SIGNAL(currentTextChanged(QString)), this , SLOT(msltShowPerson(QString)));
    mopListWidget->clear();
    QMap<unsigned int, CPerson *>::const_iterator i;
    for (i = mAll->constBegin(); i != mAll->constEnd(); ++i) {
        mopListWidget->addItem(QString::number(i.key()));
    }
    connect(mopListWidget, SIGNAL(currentTextChanged(QString)), this , SLOT(msltShowPerson(QString)));
    if(i_cur_row >= mopListWidget->count()) {
        i_cur_row = mopListWidget->count() - 1;
    }
    mopListWidget->setCurrentRow(i_cur_row);
}

void CMainWin::msltShowPerson(QString str)
{
    msCurItem = str;
    CPerson* op_person = moPersonManage.mpFindPerson(str.toInt());
    moplabJobNumberS->setText(QString::number(op_person->miGetJobNumber()));
    moplabNameS->setText(op_person->msGetName());
    moplabDepartmentS->setText(op_person->msGetDepartment());
    moplabJobTypeS->setText(op_person->msGetJobType());
    moplabSalaryS->setText(QString::number(op_person->mfGetSalary()));
}

void CMainWin::closeEvent(QCloseEvent *event)
{
}

void CMainWin::msltWidChanged(int iIndex)
{
    if (iIndex == 0) {

    } else if (iIndex == 1) {
        mvUpdateTableWidget();
    }
}

void CMainWin::mvUpdateTableWidget()
{
    mopTableWidget->clear();
    mopTableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);//整行选中的方式
    mopTableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);//禁止修改
    mopTableWidget->setColumnCount(5);
    mopTableWidget->setRowCount(mAll->count());
    mopTableWidget->setHorizontalHeaderLabels(QStringList()<<"Job Number"<<"Name"<<"Department"<<"Job Type"<<"Salary");
    mopTableWidget->verticalHeader()->setVisible(false);

    QMap<unsigned int, CPerson *>::iterator i;
    int j = 0;
    for (i = mAll->begin(); i != mAll->end(); ++i) {
        if (msJobCondition == "All"){

        } else if (i.value()->msGetJobType() != msJobCondition) {
            continue;
        }
        mopTableWidget->setItem(j,0,new QTableWidgetItem(QString::number(i.value()->miGetJobNumber())));
        mopTableWidget->setItem(j,1,new QTableWidgetItem(i.value()->msGetName()));
        mopTableWidget->setItem(j,2,new QTableWidgetItem(i.value()->msGetDepartment()));
        mopTableWidget->setItem(j,3,new QTableWidgetItem(i.value()->msGetJobType()));
        mopTableWidget->setItem(j,4,new QTableWidgetItem(QString::number(i.value()->mfGetSalary())));
        j++;
    }
}

void CMainWin::msltCbxChanged(QString str)
{
    msJobCondition = str;
    mvUpdateTableWidget();
}

void CMainWin::msltSearchClicked()
{
    QString sCustomCondition = mopletCustom->text();

    mopTableWidget->clear();
    mopTableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);//整行选中的方式
    mopTableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);//禁止修改
    mopTableWidget->setColumnCount(5);
    mopTableWidget->setHorizontalHeaderLabels(QStringList()<<"Job Number"<<"Name"<<"Department"<<"Job Type"<<"Salary");
    mopTableWidget->verticalHeader()->setVisible(false);

    QMap<unsigned int, CPerson *>::iterator i;
    int j = 0;
    for (i = mAll->begin(); i != mAll->end(); ++i) {

        if (QString::number(i.value()->miGetJobNumber()).contains(sCustomCondition) ||
                i.value()->msGetName().contains(sCustomCondition) ||
                i.value()->msGetDepartment().contains(sCustomCondition) ||
                i.value()->msGetJobType().contains(sCustomCondition) ||
                QString::number(i.value()->mfGetSalary()).contains(sCustomCondition)) {
            mopTableWidget->setItem(j,0,new QTableWidgetItem(QString::number(i.value()->miGetJobNumber())));
            mopTableWidget->setItem(j,1,new QTableWidgetItem(i.value()->msGetName()));
            mopTableWidget->setItem(j,2,new QTableWidgetItem(i.value()->msGetDepartment()));
            mopTableWidget->setItem(j,3,new QTableWidgetItem(i.value()->msGetJobType()));
            mopTableWidget->setItem(j,4,new QTableWidgetItem(QString::number(i.value()->mfGetSalary())));
            j++;

        }
    }
}

void CMainWin::setupUi()
{
    if (this->objectName().isEmpty())
        this->setObjectName(QStringLiteral("CMainWin"));
    this->resize(1012, 564);
    this->setStyleSheet(QLatin1String("QPushButton {\n"
"	font: 22pt \"Baskerville Old Face\";\n"
"	background-color: rgba(18, 62, 111, 200);\n"
"	color:rgb(230, 230, 230);\n"
"}\n"
"\n"
"QLineEdit { \n"
"	font: 16pt \"Arial Rounded MT Bold\";\n"
"}\n"
"\n"
"QComboBox { \n"
"	font: 16pt \"Arial Rounded MT Bold\"; \n"
"}\n"
"\n"
"\n"
"QLabel { \n"
"	font: 22pt \"Baskerville Old Face\";\n"
"}\n"
"\n"
"QTabWidget { \n"
"	font: 12pt \"Arial Rounded MT Bold\"; \n"
"}\n"
"\n"
"QListWidget { \n"
"	font: 15pt \"Arial Rounded MT Bold\"; \n"
"}\n"
"\n"
"QTableWidget { \n"
"	font: 12pt \"Arial Rounded MT Bold\"; \n"
"}\n"
"\n"
"\n"
""));
    mopWidCentral = new QWidget(this);
    mopWidCentral->setObjectName(QStringLiteral("mopWidCentral"));
    horizontalLayout_2 = new QHBoxLayout(mopWidCentral);
    horizontalLayout_2->setSpacing(6);
    horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
    horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
    mopWidTab = new QTabWidget(mopWidCentral);
    mopWidTab->setObjectName(QStringLiteral("mopWidTab"));
    mopWidView1 = new QWidget();
    mopWidView1->setObjectName(QStringLiteral("mopWidView1"));
    horizontalLayout = new QHBoxLayout(mopWidView1);
    horizontalLayout->setSpacing(6);
    horizontalLayout->setContentsMargins(11, 11, 11, 11);
    horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
    mopListWidget = new QListWidget(mopWidView1);
    mopListWidget->setObjectName(QStringLiteral("mopListWidget"));

    horizontalLayout->addWidget(mopListWidget);

    mopHorizontalSpacer1 = new QSpacerItem(91, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

    horizontalLayout->addItem(mopHorizontalSpacer1);

    mopGridLayout = new QGridLayout();
    mopGridLayout->setSpacing(6);
    mopGridLayout->setObjectName(QStringLiteral("mopGridLayout"));
    moplabJobNumber = new QLabel(mopWidView1);
    moplabJobNumber->setObjectName(QStringLiteral("moplabJobNumber"));

    mopGridLayout->addWidget(moplabJobNumber, 0, 0, 1, 1);

    moplabJobNumberS = new QLabel(mopWidView1);
    moplabJobNumberS->setObjectName(QStringLiteral("moplabJobNumberS"));

    mopGridLayout->addWidget(moplabJobNumberS, 0, 1, 1, 1);

    moplabName = new QLabel(mopWidView1);
    moplabName->setObjectName(QStringLiteral("moplabName"));

    mopGridLayout->addWidget(moplabName, 1, 0, 1, 1);

    moplabNameS = new QLabel(mopWidView1);
    moplabNameS->setObjectName(QStringLiteral("moplabNameS"));

    mopGridLayout->addWidget(moplabNameS, 1, 1, 1, 1);

    moplabDepartment = new QLabel(mopWidView1);
    moplabDepartment->setObjectName(QStringLiteral("moplabDepartment"));

    mopGridLayout->addWidget(moplabDepartment, 2, 0, 1, 1);

    moplabDepartmentS = new QLabel(mopWidView1);
    moplabDepartmentS->setObjectName(QStringLiteral("moplabDepartmentS"));

    mopGridLayout->addWidget(moplabDepartmentS, 2, 1, 1, 1);

    moplabJobType = new QLabel(mopWidView1);
    moplabJobType->setObjectName(QStringLiteral("moplabJobType"));

    mopGridLayout->addWidget(moplabJobType, 3, 0, 1, 1);

    moplabJobTypeS = new QLabel(mopWidView1);
    moplabJobTypeS->setObjectName(QStringLiteral("moplabJobTypeS"));

    mopGridLayout->addWidget(moplabJobTypeS, 3, 1, 1, 1);

    moplabSalary = new QLabel(mopWidView1);
    moplabSalary->setObjectName(QStringLiteral("moplabSalary"));

    mopGridLayout->addWidget(moplabSalary, 4, 0, 1, 1);

    moplabSalaryS = new QLabel(mopWidView1);
    moplabSalaryS->setObjectName(QStringLiteral("moplabSalaryS"));

    mopGridLayout->addWidget(moplabSalaryS, 4, 1, 1, 1);


    horizontalLayout->addLayout(mopGridLayout);

    mopHorizontalSpacer2 = new QSpacerItem(91, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

    horizontalLayout->addItem(mopHorizontalSpacer2);

    mopVerticalLayout = new QVBoxLayout();
    mopVerticalLayout->setSpacing(6);
    mopVerticalLayout->setObjectName(QStringLiteral("mopVerticalLayout"));
    mopVerticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

    mopVerticalLayout->addItem(mopVerticalSpacer);

    mopbtnAdd = new QPushButton(mopWidView1);
    mopbtnAdd->setObjectName(QStringLiteral("mopbtnAdd"));
    QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    sizePolicy.setHorizontalStretch(0);
    sizePolicy.setVerticalStretch(0);
    sizePolicy.setHeightForWidth(mopbtnAdd->sizePolicy().hasHeightForWidth());
    mopbtnAdd->setSizePolicy(sizePolicy);

    mopVerticalLayout->addWidget(mopbtnAdd);

    mopbtnModify = new QPushButton(mopWidView1);
    mopbtnModify->setObjectName(QStringLiteral("mopbtnModify"));
    sizePolicy.setHeightForWidth(mopbtnModify->sizePolicy().hasHeightForWidth());
    mopbtnModify->setSizePolicy(sizePolicy);

    mopVerticalLayout->addWidget(mopbtnModify);

    mopbtnDelete = new QPushButton(mopWidView1);
    mopbtnDelete->setObjectName(QStringLiteral("mopbtnDelete"));
    sizePolicy.setHeightForWidth(mopbtnDelete->sizePolicy().hasHeightForWidth());
    mopbtnDelete->setSizePolicy(sizePolicy);

    mopVerticalLayout->addWidget(mopbtnDelete);

    mopVerticalLayout->setStretch(0, 6);
    mopVerticalLayout->setStretch(1, 2);
    mopVerticalLayout->setStretch(2, 2);
    mopVerticalLayout->setStretch(3, 2);

    horizontalLayout->addLayout(mopVerticalLayout);

    horizontalLayout->setStretch(0, 2);
    horizontalLayout->setStretch(1, 1);
    horizontalLayout->setStretch(2, 4);
    horizontalLayout->setStretch(3, 1);
    horizontalLayout->setStretch(4, 2);
    mopWidTab->addTab(mopWidView1, QString());
    mopWidView2 = new QWidget();
    mopWidView2->setObjectName(QStringLiteral("mopWidView2"));
    horizontalLayout_3 = new QHBoxLayout(mopWidView2);
    horizontalLayout_3->setSpacing(6);
    horizontalLayout_3->setContentsMargins(11, 11, 11, 11);
    horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
    mopTableWidget = new QTableWidget(mopWidView2);
    mopTableWidget->setObjectName(QStringLiteral("mopTableWidget"));

    horizontalLayout_3->addWidget(mopTableWidget);

    mopVerticalLayoutR = new QVBoxLayout();
    mopVerticalLayoutR->setSpacing(6);
    mopVerticalLayoutR->setObjectName(QStringLiteral("mopVerticalLayoutR"));
    mopJobCondition = new QLabel(mopWidView2);
    mopJobCondition->setObjectName(QStringLiteral("mopJobCondition"));
    mopJobCondition->setMaximumSize(QSize(16777215, 35));

    mopVerticalLayoutR->addWidget(mopJobCondition);

    mopcbxCondition = new QComboBox(mopWidView2);
    mopcbxCondition->addItem(QString());
    mopcbxCondition->addItem(QString());
    mopcbxCondition->addItem(QString());
    mopcbxCondition->addItem(QString());
    mopcbxCondition->addItem(QString());
    mopcbxCondition->setObjectName(QStringLiteral("mopcbxCondition"));

    mopVerticalLayoutR->addWidget(mopcbxCondition);

    mopVerticalSpacerR = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

    mopVerticalLayoutR->addItem(mopVerticalSpacerR);

    mopCustomCondition = new QLabel(mopWidView2);
    mopCustomCondition->setObjectName(QStringLiteral("mopCustomCondition"));
    mopCustomCondition->setMaximumSize(QSize(16777215, 35));

    mopVerticalLayoutR->addWidget(mopCustomCondition);

    mopletCustom = new QLineEdit(mopWidView2);
    mopletCustom->setObjectName(QStringLiteral("mopletCustom"));

    mopVerticalLayoutR->addWidget(mopletCustom);

    mopbtnSearch = new QPushButton(mopWidView2);
    mopbtnSearch->setObjectName(QStringLiteral("mopbtnSearch"));
    mopbtnSearch->setMinimumSize(QSize(50, 50));

    mopVerticalLayoutR->addWidget(mopbtnSearch);

    mopVerticalLayoutR->setStretch(0, 2);
    mopVerticalLayoutR->setStretch(1, 2);
    mopVerticalLayoutR->setStretch(2, 5);
    mopVerticalLayoutR->setStretch(3, 2);
    mopVerticalLayoutR->setStretch(4, 2);
    mopVerticalLayoutR->setStretch(5, 2);

    horizontalLayout_3->addLayout(mopVerticalLayoutR);

    horizontalLayout_3->setStretch(0, 3);
    horizontalLayout_3->setStretch(1, 1);
    mopWidTab->addTab(mopWidView2, QString());

    horizontalLayout_2->addWidget(mopWidTab);

    this->setCentralWidget(mopWidCentral);

    retranslateUi();

    mopWidTab->setCurrentIndex(1);
}

void CMainWin::retranslateUi()
{
    this->setWindowTitle(QApplication::translate("CMainWin", "CMainWin", nullptr));
    moplabJobNumber->setText(QApplication::translate("CMainWin", "Job Number", nullptr));
    moplabJobNumberS->setText(QString());
    moplabName->setText(QApplication::translate("CMainWin", "Name", nullptr));
    moplabNameS->setText(QString());
    moplabDepartment->setText(QApplication::translate("CMainWin", "Department", nullptr));
    moplabDepartmentS->setText(QString());
    moplabJobType->setText(QApplication::translate("CMainWin", "Job Type", nullptr));
    moplabJobTypeS->setText(QString());
    moplabSalary->setText(QApplication::translate("CMainWin", "Salary", nullptr));
    moplabSalaryS->setText(QString());
    mopbtnAdd->setText(QApplication::translate("CMainWin", "Add", nullptr));
    mopbtnModify->setText(QApplication::translate("CMainWin", "Modify", nullptr));
    mopbtnDelete->setText(QApplication::translate("CMainWin", "Delete", nullptr));
    mopWidTab->setTabText(mopWidTab->indexOf(mopWidView1), QApplication::translate("CMainWin", "View1", nullptr));
    mopJobCondition->setText(QApplication::translate("CMainWin", "Job Condition", nullptr));
    mopcbxCondition->setItemText(0, QApplication::translate("CMainWin", "All", nullptr));
    mopcbxCondition->setItemText(1, QApplication::translate("CMainWin", "Director", nullptr));
    mopcbxCondition->setItemText(2, QApplication::translate("CMainWin", "Technician", nullptr));
    mopcbxCondition->setItemText(3, QApplication::translate("CMainWin", "Seller", nullptr));
    mopcbxCondition->setItemText(4, QApplication::translate("CMainWin", "SalesManager", nullptr));

    mopCustomCondition->setText(QApplication::translate("CMainWin", "Custom Condition", nullptr));
    mopletCustom->setText(QString());
    mopbtnSearch->setText(QApplication::translate("CMainWin", "Search", nullptr));
    mopWidTab->setTabText(mopWidTab->indexOf(mopWidView2), QApplication::translate("CMainWin", "View2", nullptr));
}
