#ifndef USERINFO_H
#define USERINFO_H

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
};

#endif // USERINFO_H
