#include "CInfoDia.h"
#include <QStringList>
#include <QMessageBox>
#include <QDebug>

CInfoDia::CInfoDia(QString* str, QWidget *parent) :
    QDialog(parent)
{
    setupUi();

    mpStr = str;
    QStringList slstStr = mpStr->split(';');
    qDebug() << slstStr;

    mopletJobNumber->setText(slstStr[1]);
    mopletJobNumber->setEnabled(false);

    msltJobTypeChanged("Director");

    connect(mopcbxJobType, SIGNAL(currentIndexChanged(QString)), this, SLOT(msltJobTypeChanged(QString)));
    mopcbxJobType->setCurrentIndex(0);

    if (slstStr[0] == "modify") {
        mopletName->setText(slstStr[2]);
        mopletDepartment->setText(slstStr[3]);
        mopcbxJobType->setCurrentText(slstStr[4]);
        mopletValue1->setText(slstStr[5]);
        mopletValue2->setText(slstStr[6]);
        mopletValue3->setText(slstStr[7]);
    }

    connect(mopbtnOk, SIGNAL(clicked()), this, SLOT(msltOkClicked()));
    connect(mopbtnCancel, SIGNAL(clicked()), this, SLOT(msltCancelClicked()));

//    msltJobTypeChanged("Director");

//    QRegExp rx("^[0-9]{8}+(\.[0-9]{4})?$");
//    QRegExpValidator *pReg = new QRegExpValidator(rx, this);
//    mopletValue1->setValidator(pReg);
//    mopletValue1->setValidator(pReg);
//    mopletValue1->setValidator(pReg);
}

CInfoDia::~CInfoDia()
{

}

void CInfoDia::msltOkClicked()
{
    if (!mbIsNumber(mopletValue1->text()) || !mbIsNumber(mopletValue2->text()) || !mbIsNumber(mopletValue3->text()) ||
        mopletName->text().isEmpty() || mopletDepartment->text().isEmpty()) {
            QMessageBox::warning(this,"Warning","The data entered is incorrect");
            return;
    }

    mpStr->clear();
    *mpStr += mopletJobNumber->text() + ";" +
              mopletName->text() + ";" +
              mopletDepartment->text() + ";" +
              mopcbxJobType->currentText() + ";" +
              mopletValue1->text() + ";" +
              mopletValue2->text() + ";" +
              mopletValue3->text();
    accept();
}

void CInfoDia::msltCancelClicked()
{
    mpStr->clear();
    *mpStr += "Cancel";
    reject();
}

void CInfoDia::msltJobTypeChanged(QString str)
{
    moplabValue1->show();
    moplabValue2->show();
    moplabValue3->hide();
    mopletValue1->show();
    mopletValue2->show();
    mopletValue3->hide();

    if (str == "Director") {
        moplabValue2->hide();
        mopletValue2->hide();
        moplabValue1->setText("Fixed Salary");
        mopletValue1->clear();
        mopletValue2->setText("0");
        mopletValue3->setText("0");
    } else if (str == "Technician") {
        moplabValue1->setText("Work Time");
        moplabValue2->setText("Hour Wage");
        mopletValue1->clear();
        mopletValue2->clear();
        mopletValue3->setText("0");
    } else if (str == "Seller") {
        moplabValue1->setText("Total Sales");
        moplabValue2->setText("Commission Rate");
        mopletValue1->clear();
        mopletValue2->clear();
        mopletValue3->setText("0");
    } else if (str == "SalesManager") {
        moplabValue3->show();
        mopletValue3->show();
        moplabValue1->setText("Basic Salary");
        moplabValue2->setText("Total Sales");
        moplabValue3->setText("Commission Rate");
        mopletValue1->clear();
        mopletValue2->clear();
        mopletValue3->clear();
    }
}

bool CInfoDia::mbIsNumber(const QString& mStr)
{
    double tmp;
    int n = sscanf_s(mStr.toLatin1().data(), "%lf", &tmp);
    return n != 0;
}

void CInfoDia::closeEvent(QCloseEvent *event)
{
    mpStr->clear();
    *mpStr += "Cancel";
}

void CInfoDia::setupUi()
{
    this->resize(407, 354);
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
    gridLayout = new QGridLayout(this);
    mopHorizontalSpacerL = new QSpacerItem(80, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

    gridLayout->addItem(mopHorizontalSpacerL, 1, 0, 1, 1);

    mopHorizontalSpacerR = new QSpacerItem(80, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

    gridLayout->addItem(mopHorizontalSpacerR, 1, 2, 1, 1);

    mopVerticalSpacerU = new QSpacerItem(20, 48, QSizePolicy::Minimum, QSizePolicy::Expanding);

    gridLayout->addItem(mopVerticalSpacerU, 0, 1, 1, 1);

    mopVerticalSpacerD = new QSpacerItem(20, 47, QSizePolicy::Minimum, QSizePolicy::Expanding);

    gridLayout->addItem(mopVerticalSpacerD, 2, 1, 1, 1);

    mopGridLayout = new QGridLayout();
    moplabValue3 = new QLabel(this);

    mopGridLayout->addWidget(moplabValue3, 6, 0, 1, 1);

    mopletValue3 = new QLineEdit(this);

    mopGridLayout->addWidget(mopletValue3, 6, 1, 1, 1);

    mopletValue2 = new QLineEdit(this);

    mopGridLayout->addWidget(mopletValue2, 5, 1, 1, 1);

    moplabValue2 = new QLabel(this);

    mopGridLayout->addWidget(moplabValue2, 5, 0, 1, 1);

    moplabValue1 = new QLabel(this);

    mopGridLayout->addWidget(moplabValue1, 4, 0, 1, 1);

    moplabJobNumber = new QLabel(this);

    mopGridLayout->addWidget(moplabJobNumber, 0, 0, 1, 1);

    mopletDepartment = new QLineEdit(this);

    mopGridLayout->addWidget(mopletDepartment, 2, 1, 1, 1);

    mopletValue1 = new QLineEdit(this);

    mopGridLayout->addWidget(mopletValue1, 4, 1, 1, 1);

    moplabDepartment = new QLabel(this);

    mopGridLayout->addWidget(moplabDepartment, 2, 0, 1, 1);

    mopletName = new QLineEdit(this);

    mopGridLayout->addWidget(mopletName, 1, 1, 1, 1);

    mopcbxJobType = new QComboBox(this);
    mopcbxJobType->addItem(QString());
    mopcbxJobType->addItem(QString());
    mopcbxJobType->addItem(QString());
    mopcbxJobType->addItem(QString());

    mopGridLayout->addWidget(mopcbxJobType, 3, 1, 1, 1);

    moplabName = new QLabel(this);

    mopGridLayout->addWidget(moplabName, 1, 0, 1, 1);

    moplabJobType = new QLabel(this);

    mopGridLayout->addWidget(moplabJobType, 3, 0, 1, 1);

    mopletJobNumber = new QLineEdit(this);

    mopGridLayout->addWidget(mopletJobNumber, 0, 1, 1, 1);

    mopbtnOk = new QPushButton(this);
    QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Maximum);
    sizePolicy.setHorizontalStretch(0);
    sizePolicy.setVerticalStretch(0);
    sizePolicy.setHeightForWidth(mopbtnOk->sizePolicy().hasHeightForWidth());
    mopbtnOk->setSizePolicy(sizePolicy);
    mopbtnOk->setMaximumSize(QSize(120, 16777215));

    mopGridLayout->addWidget(mopbtnOk, 10, 0, 1, 1);

    mopbtnCancel = new QPushButton(this);
    sizePolicy.setHeightForWidth(mopbtnCancel->sizePolicy().hasHeightForWidth());
    mopbtnCancel->setSizePolicy(sizePolicy);
    mopbtnCancel->setMaximumSize(QSize(120, 16777215));

    mopGridLayout->addWidget(mopbtnCancel, 10, 1, 1, 1);

    gridLayout->addLayout(mopGridLayout, 1, 1, 1, 1);

    retranslateUi();
}

void CInfoDia::retranslateUi()
{
    this->setWindowTitle(QApplication::translate("CInfoDia", "Info", nullptr));
    moplabValue3->setText(QApplication::translate("CInfoDia", "Value3", nullptr));
    moplabValue2->setText(QApplication::translate("CInfoDia", "Value2", nullptr));
    moplabValue1->setText(QApplication::translate("CInfoDia", "Value1", nullptr));
    moplabJobNumber->setText(QApplication::translate("CInfoDia", "Job Number", nullptr));
    moplabDepartment->setText(QApplication::translate("CInfoDia", "Department", nullptr));
    mopcbxJobType->setItemText(0, QApplication::translate("CInfoDia", "Director", nullptr));
    mopcbxJobType->setItemText(1, QApplication::translate("CInfoDia", "Technician", nullptr));
    mopcbxJobType->setItemText(2, QApplication::translate("CInfoDia", "Seller", nullptr));
    mopcbxJobType->setItemText(3, QApplication::translate("CInfoDia", "SalesManager", nullptr));

    moplabName->setText(QApplication::translate("CInfoDia", "Name", nullptr));
    moplabJobType->setText(QApplication::translate("CInfoDia", "Job Type", nullptr));
    mopbtnOk->setText(QApplication::translate("CInfoDia", "Ok", nullptr));
    mopbtnCancel->setText(QApplication::translate("CInfoDia", "Cancel", nullptr));
}
