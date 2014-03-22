#ifndef COMMON_H
#define COMMON_H

#include <QDir>

static const QString g_Company = "Piekny";
static const QString g_Project = "Gonzales";
static const QString g_Users = "Users";
static const QString file_qAs = ".qas";


enum QAFileVersion
{
    QAUnsupportedFileVersion = 0,
    QAFileVersion1 = 1
};

inline QString getFilePathToQas(const QString &userName)
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

#endif // COMMON_H
