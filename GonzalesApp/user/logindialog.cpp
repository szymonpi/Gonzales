#include "logindialog.h"
#include "ui_logindialog.h"
#include "dialogcreateaccount.h"
#include "accountsprovider.h"

LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDialog),
    m_dialogCreateAccount(this),
    m_provider()
{
    setAttribute(Qt::WA_DeleteOnClose, false);
    ui->setupUi(this);

    connect(&m_dialogCreateAccount,SIGNAL(accountCreated(const QString&)),this, SLOT(onAccountCreated(const QString&)));

    QStringList accounts = m_provider.getAccounts();
    if(accounts.isEmpty())
    {
        m_dialogCreateAccount.setModal(true);
        m_dialogCreateAccount.exec();
    }
    else
    {
        ui->comboBoxAccounts->addItems(accounts);
    }

}

LoginDialog::~LoginDialog()
{
    delete ui;
}

void LoginDialog::onAccountCreated(const QString & str)
{
    ui->comboBoxAccounts->addItem(str);
    ui->comboBoxAccounts->setCurrentText(str);
    ui->lineEditPassword->setFocus();
}

UserInfo LoginDialog::getUserInfo()
{
    return m_info;
}

void LoginDialog::on_toolButtonCreateNewAccount_clicked()
{
    m_dialogCreateAccount.setModal(true);
    m_dialogCreateAccount.exec();
}

void LoginDialog::on_pushButtonLogin_clicked()
{
    Authorizer authorizer;
    m_info = authorizer.authorize(ui->comboBoxAccounts->currentText(), ui->lineEditPassword->text());
    if(m_info.isAuthorized)
    {
        close();
        return;
    }
    QPalette palette;
    palette.setColor(QPalette::Text, QColor(255, 0, 0));
    ui->lineEditPassword->setPalette(palette);
}
