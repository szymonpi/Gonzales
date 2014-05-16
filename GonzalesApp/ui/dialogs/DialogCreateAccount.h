#pragma once

#include <QDialog>

namespace Ui {
class DialogCreateAccount;
}

class DialogCreateAccount : public QDialog
{
    Q_OBJECT

public:
    explicit DialogCreateAccount(QWidget *parent = 0);
    ~DialogCreateAccount();

private slots:
    void on_pushButtonCreate_clicked();
    void on_pushButtonCancel_clicked();

signals:
    void accountCreated(const QString &str);

private:
    Ui::DialogCreateAccount *ui;
    QString m_createdAccountName;
};
