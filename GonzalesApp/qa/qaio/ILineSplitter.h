#pragma once
#include <QStringList>

class ILineSplitter
{
public:
    ~ILineSplitter(){}
    virtual QStringList splitLine(const QString &line) = 0;
};
