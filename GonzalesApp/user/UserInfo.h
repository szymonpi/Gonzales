#pragma once
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



