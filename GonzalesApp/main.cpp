#include "ui/mainwindow.h"
#include <QApplication>

#include "User/UserInfo.h"
#include "ui/dialogs/LoginDialog.h"
#include "QARepositoryFactory.h"
#include "ImportHandlerFactory.h"
#include "TeacherControllerFactory.h"

///@todo add algorithm to Node for iterating!
///@todo add validation in appendQA dialog
///@todo add new import features like "Q: A:" importer xml importer?

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
    TeacherControllerFactory teacherControllerFactory(repository);

    MainWindow w{m_userInfo,
                 repository,
                 importFactory.create(),
                 teacherControllerFactory.create()};
    w.show();

    return a.exec();
}
