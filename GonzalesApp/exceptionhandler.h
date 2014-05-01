#ifndef EXCEPTIONHANDLER_H
#define EXCEPTIONHANDLER_H
#include <QString>
#include <QMessageBox>
#include "IExceptionHandler.h"

class ExceptionHandler: public IExceptionHandler
{
public:
    void handleException(const QString &message, const QString &errorName) const;
};

#endif // EXCEPTIONHANDLER_H
