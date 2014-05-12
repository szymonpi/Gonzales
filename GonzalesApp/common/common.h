#ifndef COMMON_H
#define COMMON_H

#include <QDir>

static const QString g_Company = "Piekny";
static const QString g_Project = "Gonzales";
static const QString g_Users = "Users";
static const QString file_qAs = ".qas";

enum DataRole
{
    DATA_ROLE_QA_POINTER = 1
};


enum QAFileVersion
{
    QAUnsupportedFileVersion = 0,
    QAFileVersion1 = 1
};

#endif // COMMON_H
