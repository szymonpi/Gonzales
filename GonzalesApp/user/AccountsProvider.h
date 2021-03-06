#pragma once
#include <memory>

#include "../common/qtproxies/ApplicationSettings.h"

class AccountsProvider
{
public:
    AccountsProvider(std::shared_ptr<IApplicationSettings> settings = std::make_shared<ApplicationSettings>()):
    m_applicationSettings(settings)
    {}

    QStringList getAccounts()
    {
        m_applicationSettings->beginGroup(g_Users);
        return m_applicationSettings->childGroups();
    }

private:
    std::shared_ptr<IApplicationSettings> m_applicationSettings;
};
