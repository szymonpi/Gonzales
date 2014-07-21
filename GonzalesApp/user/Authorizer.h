#pragma once

#include "string"
#include "CredentialsValidator.h"
#include <memory>
#include "../common/qtproxies/ApplicationSettings.h"
#include "UserInfo.h"
#include "../common/Common.h"

class Authorizer
{
public:
    Authorizer(std::shared_ptr<IApplicationSettings> p_settings = std::make_shared<ApplicationSettings>()):
        m_settings(p_settings)
    {}

    UserInfo authorize(const QString &login, const QString &password);
private:
    std::shared_ptr<IApplicationSettings> m_settings;
};
