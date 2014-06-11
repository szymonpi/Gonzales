#include "ExceptionHandler.h"


void ExceptionHandler::handleException(const QString &message, const QString &errorName) const
{
    QMessageBox messahe;
    messahe.setWindowTitle(errorName);
    messahe.setText(message);
    messahe.exec();
}
