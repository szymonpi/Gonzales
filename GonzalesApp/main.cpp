#include "ui/mainwindow.h"
#include <QApplication>

#include "User/UserInfo.h"
#include "ui/dialogs/LoginDialog.h"

///@todo: move factories there from mainwindow
///@todo add algorithm to Node for iterating!
///@todo remove unnecessary files from repository
///@todo add validation in appendQA dialog

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    LoginDialog loginDialog;
    loginDialog.setModal(true);
    loginDialog.exec();
    if(!loginDialog.isAuthorized()) // <- move to main.cpp
        exit(0);
    UserInfo m_userInfo = loginDialog.getUserInfo();

    MainWindow w{m_userInfo};
    w.show();

    return a.exec();
}
