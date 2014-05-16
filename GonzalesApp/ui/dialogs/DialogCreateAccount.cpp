#include "dialogcreateaccount.h"
#include "ui_dialogcreateaccount.h"
#include "user/accountcreator.h"
#include <QMessageBox>

DialogCreateAccount::DialogCreateAccount(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogCreateAccount)
{
    ui->setupUi(this);
}

DialogCreateAccount::~DialogCreateAccount()
{
    delete ui;
}

void DialogCreateAccount::on_pushButtonCreate_clicked()
{
    AccountCreator aC;
    try
    {
        aC.create(ui->lineEditLogin->text(), ui->lineEditPassword->text(), ui->lineEditConfirmedPassword->text());
        emit accountCreated(ui->lineEditLogin->text());
        close();
    }
    catch(const PasswordException &e)
    {
        QMessageBox exceptionBox(this);
        exceptionBox.setWindowTitle("Account create error");
        exceptionBox.setText(e.what());
        exceptionBox.exec();
    }
    catch(const LoginException &e)
    {
        QMessageBox exceptionBox(this);
        exceptionBox.setWindowTitle("Account create error");
        exceptionBox.setText(e.what());
        exceptionBox.exec();
    }
}

void DialogCreateAccount::on_pushButtonCancel_clicked()
{
    close();
}
