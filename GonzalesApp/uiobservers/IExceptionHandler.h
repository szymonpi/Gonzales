#pragma once

#include <QString>

class IExceptionHandler
{
public:
    virtual void handleException(const QString &message, const QString &errorName) const = 0;
    virtual ~IExceptionHandler(){}
};
