#pragma once
#include "IQAsFilePathProvider.h"
#include "../User/UserInfo.h"

class QAsFilePathProvider: public IQAsFilePathProvider
{
public:
    QAsFilePathProvider(const UserInfo &userInfo):
        m_userInfo(userInfo)
    {
        QDir homeDirectory = QDir::homePath();
        m_path = homeDirectory.path()+"/"+g_Company+"/"+g_Project+"/"+m_userInfo.login+qAsFileExtension;
    }

bool isCreateFilePathNeeded()
    {
        QDir homeDirectory = QDir::homePath();
        if(!homeDirectory.cd(g_Company+"/"+g_Project+"/"))
            return true;
        return false;
    }

bool isQAsFileExist()
    {
        QDir homeDirectory = QDir::homePath();
        QFile file(QDir::homePath()+"/"+g_Company+"/"+g_Project+"/"+m_userInfo.login+qAsFileExtension);
        if(!file.exists())
            return false;
        return true;
    }

void createQAsFilePath()
    {
    if(!isCreateFilePathNeeded())
        return;
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
        m_path = homeDirectory.path()+"/"+m_userInfo.login+qAsFileExtension;
    }

QString getPath() const
{
    return m_path;
}

private:
    QString m_path;
    const UserInfo &m_userInfo;
};
