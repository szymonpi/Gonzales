#include "credentialsvalidator.h"
#include <QRegExp>

void CredentialsValidator::validate(const QString &login, const QString &password) const
{
    checkLogin(login);
    checkPassword(password);
}

void CredentialsValidator::validate(const QString &login, const QString &password, const QString &confirmedPassword) const
{
    checkLogin(login);
    checkPassword(password);
    checkConfirmedPassword(password, confirmedPassword);
}

void CredentialsValidator::checkLogin(const QString &login) const
{
    QRegExp loginExp("\\w{3,30}");
    if(!loginExp.exactMatch(login))
        throw LoginException("Login didn't match requirements");
}

void CredentialsValidator::checkConfirmedPassword(const QString &password, const QString &confirmedPassword) const
{
    if(password != confirmedPassword)
        throw PasswordException("Password and confirmedPassword are not the same");
}

void CredentialsValidator::checkPassword(const QString &password) const
{
    QRegExp passwordExp("\\S{3,30}");
    if(!passwordExp.exactMatch(password))
        throw PasswordException("Password didn't match requirements");
}
