#include "ui/mainwindow.h"
#include <QApplication>
//szymon
#include "user/UserInfo.h"
#include "ui/dialogs/LoginDialog.h"
#include "QARepositoryFactory.h"
#include "ImportHandlerFactory.h"
#include "TeacherControllerFactory.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    LoginDialog loginDialog;
    loginDialog.setModal(true);
    loginDialog.exec();
    if(!loginDialog.isAuthorized())
        exit(0);
    UserInfo m_userInfo = loginDialog.getUserInfo();

    QARepositoryFactory qARepositoryFactory;
    auto repository = qARepositoryFactory.create(m_userInfo);
    ImportHandlerFactory importFactory(repository);

    MainWindow w{m_userInfo,
                 repository,
                 importFactory.create()};
    w.show();

    return a.exec();
}
