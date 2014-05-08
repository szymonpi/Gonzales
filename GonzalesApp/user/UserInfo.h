#ifndef USERINFO_H
#define USERINFO_H
#include <QDir>
#include "../Common/common.h"

struct UserInfo
{
    UserInfo():
        login(""),
        isAuthorized(false)
    {

    }

    UserInfo(const QString &login):
        login(login),
        isAuthorized(false)
    {
    }

    QString login;
    bool isAuthorized;
    QString path;
};

class IPathCreator
{
    virtual QString createQAsPath(const QString& userName) = 0;
    ~IPathCreator(){}
};

class PathCreator
{
public:
    QString createQAsFilePath(const QString& userName)
    {
        QDir homeDirectory = QDir::homePath();
        if(!homeDirectory.cd(g_Company))
        {
            homeDirectory.mkdir(g_Company);
            homeDirectory.cd(g_Company);
        }
        if(!homeDirectory.cd(g_Company))
        {
            homeDirectory.mkdir(g_Project);
            homeDirectory.cd(g_Project);
        }
        QString path = homeDirectory.path()+"/"+userName+file_qAs;
        return path;
    }
};

#endif // USERINFO_H
