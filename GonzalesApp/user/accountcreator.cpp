#include "accountcreator.h"
#include <QString>
#include <QRegExp>
#include <QSettings>

AccountCreator::AccountCreator(std::shared_ptr<IApplicationSettings>
                               settings, std::shared_ptr<ICredentialsValidatorFactory> validatorFactory):
    settings(settings),
    m_validatorFactory(validatorFactory)
{
}

void AccountCreator::checkAvailability(const QString &login)
{
    if(settings->contains(g_Users+"/"+login))
        throw PasswordException("Login already exist");
}

void AccountCreator::checkCanCreateAccount(const QString &confirmedPassword, const QString &login, const QString &password)
{
    std::shared_ptr<ICredentialsValidator> validator = m_validatorFactory->create();
    validator->validate(login, password, confirmedPassword);
    checkAvailability(login);
}

void AccountCreator::createEntryInApplicationSettings(const QString &password, const QString &login)
{
    settings->setValue(g_Users+"/", login);
    settings->setValue(g_Users+"/"+login+"/password", password);
}

void AccountCreator::create(const QString &login, const QString &password, const QString &confirmedPassword)
{
    checkCanCreateAccount(confirmedPassword, login, password);
    createEntryInApplicationSettings(password, login);
}
