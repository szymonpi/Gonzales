#pragma once
#include <QString>
#include "icredentialsvalidator.h"

class LoginException: public std::runtime_error
{
public:
    LoginException(const std::string &what):
        runtime_error(what)
    {
    }

};

class PasswordException: public std::runtime_error
{
public:
    PasswordException(const std::string &what):
        runtime_error(what)
    {
    }
};

class CredentialsValidator: public ICredentialsValidator
{
public:
    virtual void validate(const QString &login, const QString &password) const;
    void validate(const QString &login, const QString &password, const QString &confirmedPassword) const;

    void checkConfirmedPassword(const QString &password, const QString &confirmedPassword) const;
private:
    void checkLogin(const QString &login) const;
    void checkPassword(const QString &password) const;
};
