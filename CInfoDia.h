#ifndef CINFODIA_H
#define CINFODIA_H

#include <QDialog>
#include <QCloseEvent>
#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>

class CInfoDia : public QDialog
{
    Q_OBJECT

public:
    explicit CInfoDia(QString* str,QWidget *parent = 0);
    ~CInfoDia();

public slots:
    void msltJobTypeChanged(QString str);
    void msltOkClicked();
    void msltCancelClicked();

    bool mbIsNumber(const QString& mStr);

private:
    QString* mpStr;

    virtual void closeEvent(QCloseEvent *event);

private:
    void retranslateUi();
    void setupUi();

    QGridLayout *gridLayout;
    QSpacerItem *mopHorizontalSpacerL;
    QSpacerItem *mopHorizontalSpacerR;
    QSpacerItem *mopVerticalSpacerU;
    QSpacerItem *mopVerticalSpacerD;
    QGridLayout *mopGridLayout;
    QLabel *moplabValue3;
    QLineEdit *mopletValue3;
    QLineEdit *mopletValue2;
    QLabel *moplabValue2;
    QLabel *moplabValue1;
    QLabel *moplabJobNumber;
    QLineEdit *mopletDepartment;
    QLineEdit *mopletValue1;
    QLabel *moplabDepartment;
    QLineEdit *mopletName;
    QComboBox *mopcbxJobType;
    QLabel *moplabName;
    QLabel *moplabJobType;
    QLineEdit *mopletJobNumber;
    QPushButton *mopbtnOk;
    QPushButton *mopbtnCancel;
};

#endif // CINFODIA_H
