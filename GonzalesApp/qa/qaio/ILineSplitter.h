#pragma once
#include <QStringList>

class ILineSplitter
{
public:
    virtual ~ILineSplitter(){}
    virtual QStringList splitLine(const QString &line) = 0;
};
