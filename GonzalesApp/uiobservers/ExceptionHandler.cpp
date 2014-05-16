#include "exceptionhandler.h"


void ExceptionHandler::handleException(const QString &message, const QString &errorName) const
{
    QMessageBox saveMessage;
    saveMessage.setWindowTitle(errorName);
    saveMessage.setText(message);
    saveMessage.exec();
}
