#pragma once

#include "string"
#include "credentialsvalidator.h"
#include <memory>
#include "../common/qtproxies/ApplicationSettings.h"
#include "UserInfo.h"
#include "../common/common.h"

class Authorizer
{
public:
    Authorizer(std::shared_ptr<IApplicationSettings> p_settings = std::make_shared<ApplicationSettings>()):
        m_settings(p_settings)
    {}

    UserInfo authorize(const QString &login, const QString &password)
    {
        m_settings->beginGroup(g_Users);
        if(!m_settings->contains(login+"/password"))
            return UserInfo(login);
        if(m_settings->value(login+"/password","") != password)
            return UserInfo(login);

        UserInfo info(login);
        info.isAuthorized = true;
        return info;
    }
private:
    std::shared_ptr<IApplicationSettings> m_settings;
};
