#ifndef IEXCEPTIONHANDLER_H
#define IEXCEPTIONHANDLER_H

#include <QString>

class IExceptionHandler
{
public:
    virtual void handleException(const QString &message, const QString &errorName) const = 0;
    virtual ~IExceptionHandler(){}
};

#endif // IEXCEPTIONHANDLER_H
