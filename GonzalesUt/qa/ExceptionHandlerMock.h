#ifndef EXCEPTIONHANDLERMOCK_H
#define EXCEPTIONHANDLERMOCK_H
#include "../../GonzalesApp/uiobservers/IExceptionHandler.h"
#include "../gmock.h"

class ExceptionHandlerMock: public IExceptionHandler
{
public:
    MOCK_CONST_METHOD2(handleException, void(const QString &, const QString &));
};

#endif // EXCEPTIONHANDLERMOCK_H
