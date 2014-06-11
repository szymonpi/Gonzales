/********************************************************************************
** Form generated from reading UI file 'logindialog.ui'
**
** Created by: Qt User Interface Compiler version 5.2.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGINDIALOG_H
#define UI_LOGINDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_LoginDialog
{
public:
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout_2;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout;
    QComboBox *comboBoxAccounts;
    QLineEdit *lineEditPassword;
    QPushButton *pushButtonLogin;
    QToolButton *toolButtonCreateNewAccount;

    void setupUi(QDialog *LoginDialog)
    {
        if (LoginDialog->objectName().isEmpty())
            LoginDialog->setObjectName(QStringLiteral("LoginDialog"));
        LoginDialog->resize(414, 177);
        verticalLayout_3 = new QVBoxLayout(LoginDialog);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        groupBox = new QGroupBox(LoginDialog);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        verticalLayout = new QVBoxLayout(groupBox);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        comboBoxAccounts = new QComboBox(groupBox);
        comboBoxAccounts->setObjectName(QStringLiteral("comboBoxAccounts"));
        comboBoxAccounts->setEditable(false);
        comboBoxAccounts->setMaxVisibleItems(100);

        verticalLayout->addWidget(comboBoxAccounts);

        lineEditPassword = new QLineEdit(groupBox);
        lineEditPassword->setObjectName(QStringLiteral("lineEditPassword"));
        lineEditPassword->setEchoMode(QLineEdit::Password);

        verticalLayout->addWidget(lineEditPassword);


        verticalLayout_2->addWidget(groupBox);

        pushButtonLogin = new QPushButton(LoginDialog);
        pushButtonLogin->setObjectName(QStringLiteral("pushButtonLogin"));

        verticalLayout_2->addWidget(pushButtonLogin);


        horizontalLayout->addLayout(verticalLayout_2);

        toolButtonCreateNewAccount = new QToolButton(LoginDialog);
        toolButtonCreateNewAccount->setObjectName(QStringLiteral("toolButtonCreateNewAccount"));
        QSizePolicy sizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
        sizePolicy.setHorizontalStretch(32);
        sizePolicy.setVerticalStretch(32);
        sizePolicy.setHeightForWidth(toolButtonCreateNewAccount->sizePolicy().hasHeightForWidth());
        toolButtonCreateNewAccount->setSizePolicy(sizePolicy);
        toolButtonCreateNewAccount->setMinimumSize(QSize(32, 64));

        horizontalLayout->addWidget(toolButtonCreateNewAccount);


        verticalLayout_3->addLayout(horizontalLayout);

        QWidget::setTabOrder(lineEditPassword, pushButtonLogin);
        QWidget::setTabOrder(pushButtonLogin, comboBoxAccounts);
        QWidget::setTabOrder(comboBoxAccounts, toolButtonCreateNewAccount);

        retranslateUi(LoginDialog);

        QMetaObject::connectSlotsByName(LoginDialog);
    } // setupUi

    void retranslateUi(QDialog *LoginDialog)
    {
        LoginDialog->setWindowTitle(QApplication::translate("LoginDialog", "Login to gonzales!", 0));
        groupBox->setTitle(QApplication::translate("LoginDialog", "credentials", 0));
        comboBoxAccounts->setCurrentText(QString());
        lineEditPassword->setPlaceholderText(QApplication::translate("LoginDialog", "password", 0));
        pushButtonLogin->setText(QApplication::translate("LoginDialog", "login", 0));
        toolButtonCreateNewAccount->setText(QApplication::translate("LoginDialog", "Create new Account", 0));
    } // retranslateUi

};

namespace Ui {
    class LoginDialog: public Ui_LoginDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGINDIALOG_H
