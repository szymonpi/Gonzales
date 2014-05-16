#pragma once
#include <QString>
#include <QMessageBox>
#include "IExceptionHandler.h"

class ExceptionHandler: public IExceptionHandler
{
public:
    void handleException(const QString &message, const QString &errorName) const;
};
