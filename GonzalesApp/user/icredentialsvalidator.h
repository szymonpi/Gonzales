#ifndef ICREDENTIALSVALIDATOR_H
#define ICREDENTIALSVALIDATOR_H

#include "QString"

class ICredentialsValidator
{
public:
    virtual void validate(const QString &login, const QString &password) const = 0;
    virtual void validate(const QString &login, const QString &password, const QString &confirmedPassword) const = 0;
};

#endif // ICREDENTIALSVALIDATOR_H
