#pragma once
#include <QString>

class IQAsFilePathProvider
{
public:
    virtual QString getPath() const = 0;
    ~IQAsFilePathProvider(){}
};
