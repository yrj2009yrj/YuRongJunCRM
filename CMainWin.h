#ifndef CMAINWIN_H
#define CMAINWIN_H
#include <QMainWindow>
#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "CPersonManage.h"

class CMainWin : public QMainWindow
{
    Q_OBJECT

public:
    explicit CMainWin(QWidget *parent = 0);
    ~CMainWin();

private slots:
    void msltAddClicked();
    void msltModifyClicked();
    void msltDeleteClicked();

    void msltShowPerson(QString str);
    void msltWidChanged(int iIndex);

    void msltCbxChanged(QString str);
    void msltSearchClicked();

private:
    CPersonManage moPersonManage;
    QMap<unsigned int, CPerson *>* mAll;
    QString msCurItem;
    QString msJobCondition;

    void mvUpdateTableWidget();
    void mvUpdateListWidget();
    virtual void closeEvent(QCloseEvent *event);

    void setupUi();
    void retranslateUi();

private:
    QWidget *mopWidCentral;
    QHBoxLayout *horizontalLayout_2;
    QTabWidget *mopWidTab;
    QWidget *mopWidView1;
    QHBoxLayout *horizontalLayout;
    QListWidget *mopListWidget;
    QSpacerItem *mopHorizontalSpacer1;
    QGridLayout *mopGridLayout;
    QLabel *moplabJobNumber;
    QLabel *moplabJobNumberS;
    QLabel *moplabName;
    QLabel *moplabNameS;
    QLabel *moplabDepartment;
    QLabel *moplabDepartmentS;
    QLabel *moplabJobType;
    QLabel *moplabJobTypeS;
    QLabel *moplabSalary;
    QLabel *moplabSalaryS;
    QSpacerItem *mopHorizontalSpacer2;
    QVBoxLayout *mopVerticalLayout;
    QSpacerItem *mopVerticalSpacer;
    QPushButton *mopbtnAdd;
    QPushButton *mopbtnModify;
    QPushButton *mopbtnDelete;
    QWidget *mopWidView2;
    QHBoxLayout *horizontalLayout_3;
    QTableWidget *mopTableWidget;
    QVBoxLayout *mopVerticalLayoutR;
    QLabel *mopJobCondition;
    QComboBox *mopcbxCondition;
    QSpacerItem *mopVerticalSpacerR;
    QLabel *mopCustomCondition;
    QLineEdit *mopletCustom;
    QPushButton *mopbtnSearch;
};

#endif // CMAINWIN_H
