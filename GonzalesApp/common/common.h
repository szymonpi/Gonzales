#pragma once

#include <QDir>

static const QString g_Company = "Piekny";
static const QString g_Project = "Gonzales";
static const QString g_Users = "Users";
static const QString qAsFileExtension = ".qas";

enum QAFileVersion
{
    QAUnsupportedFileVersion = 0,
    QAFileVersion1 = 1
};

enum NodeInfoRole
{
    NODE_INFO_ROLE_CHECKED = 1
};
