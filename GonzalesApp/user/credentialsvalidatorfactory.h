#ifndef CREDENTIALSVALIDATORFACTORY_H
#define CREDENTIALSVALIDATORFACTORY_H

#include "memory"
#include "credentialsvalidator.h"

class ICredentialsValidatorFactory
{
public:
    virtual std::shared_ptr<ICredentialsValidator> create() const = 0;
    virtual ~ICredentialsValidatorFactory(){}
};

class CredentialsValidatorFactory: public ICredentialsValidatorFactory
{
public:
    std::shared_ptr<ICredentialsValidator> create() const
    {
        return std::make_shared<CredentialsValidator>();
    }

};

#endif // CREDENTIALSVALIDATORFACTORY_H
