/********************************************************************************
** Form generated from reading UI file 'dialogcreateaccount.ui'
**
** Created by: Qt User Interface Compiler version 5.2.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOGCREATEACCOUNT_H
#define UI_DIALOGCREATEACCOUNT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_DialogCreateAccount
{
public:
    QVBoxLayout *verticalLayout;
    QLineEdit *lineEditLogin;
    QLineEdit *lineEditPassword;
    QLineEdit *lineEditConfirmedPassword;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButtonCancel;
    QPushButton *pushButtonCreate;

    void setupUi(QDialog *DialogCreateAccount)
    {
        if (DialogCreateAccount->objectName().isEmpty())
            DialogCreateAccount->setObjectName(QStringLiteral("DialogCreateAccount"));
        DialogCreateAccount->resize(312, 199);
        verticalLayout = new QVBoxLayout(DialogCreateAccount);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        lineEditLogin = new QLineEdit(DialogCreateAccount);
        lineEditLogin->setObjectName(QStringLiteral("lineEditLogin"));

        verticalLayout->addWidget(lineEditLogin);

        lineEditPassword = new QLineEdit(DialogCreateAccount);
        lineEditPassword->setObjectName(QStringLiteral("lineEditPassword"));
        lineEditPassword->setInputMethodHints(Qt::ImhHiddenText|Qt::ImhNoAutoUppercase|Qt::ImhNoPredictiveText|Qt::ImhSensitiveData);
        lineEditPassword->setEchoMode(QLineEdit::Password);

        verticalLayout->addWidget(lineEditPassword);

        lineEditConfirmedPassword = new QLineEdit(DialogCreateAccount);
        lineEditConfirmedPassword->setObjectName(QStringLiteral("lineEditConfirmedPassword"));
        lineEditConfirmedPassword->setEchoMode(QLineEdit::Password);

        verticalLayout->addWidget(lineEditConfirmedPassword);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        pushButtonCancel = new QPushButton(DialogCreateAccount);
        pushButtonCancel->setObjectName(QStringLiteral("pushButtonCancel"));

        horizontalLayout->addWidget(pushButtonCancel);

        pushButtonCreate = new QPushButton(DialogCreateAccount);
        pushButtonCreate->setObjectName(QStringLiteral("pushButtonCreate"));

        horizontalLayout->addWidget(pushButtonCreate);


        verticalLayout->addLayout(horizontalLayout);


        retranslateUi(DialogCreateAccount);

        QMetaObject::connectSlotsByName(DialogCreateAccount);
    } // setupUi

    void retranslateUi(QDialog *DialogCreateAccount)
    {
        DialogCreateAccount->setWindowTitle(QApplication::translate("DialogCreateAccount", "Create new account", 0));
        lineEditLogin->setPlaceholderText(QApplication::translate("DialogCreateAccount", "login", 0));
        lineEditPassword->setPlaceholderText(QApplication::translate("DialogCreateAccount", "password", 0));
        lineEditConfirmedPassword->setPlaceholderText(QApplication::translate("DialogCreateAccount", "confirm your password", 0));
        pushButtonCancel->setText(QApplication::translate("DialogCreateAccount", "cancel", 0));
        pushButtonCreate->setText(QApplication::translate("DialogCreateAccount", "create", 0));
    } // retranslateUi

};

namespace Ui {
    class DialogCreateAccount: public Ui_DialogCreateAccount {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOGCREATEACCOUNT_H
