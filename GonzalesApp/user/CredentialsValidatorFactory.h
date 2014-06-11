#pragma once

#include "memory"
#include "CredentialsValidator.h"

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
