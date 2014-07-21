#pragma once
#include <QStringList>

class ILineToImportSplitter
{
public:
    virtual ~ILineToImportSplitter(){}
    virtual QStringList splitLine(const QString &line) = 0;
};
