#pragma once
#include <stdexcept>
#include <memory>
#include "../common/qtproxies/ApplicationSettings.h"
#include "CredentialsValidator.h"
#include "CredentialsValidatorFactory.h"

class QString;

class AccountCreator
{
public:
    AccountCreator(std::shared_ptr<IApplicationSettings> settings = std::make_shared<ApplicationSettings>(),
                   std::shared_ptr<ICredentialsValidatorFactory> validatorFactory = std::make_shared<CredentialsValidatorFactory>());
    void create(const QString &login, const QString &password, const QString &confirmedPassword);

private:
    void checkAvailability(const QString &login);
    void checkCanCreateAccount(const QString &confirmedPassword, const QString &login, const QString &password);
    void createEntryInApplicationSettings(const QString &password, const QString &login);
    std::shared_ptr<IApplicationSettings> settings;
    std::shared_ptr<ICredentialsValidatorFactory> m_validatorFactory;
};
