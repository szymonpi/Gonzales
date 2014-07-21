#include "Authorizer.h"



UserInfo Authorizer::authorize(const QString &login, const QString &password)
{
    m_settings->beginGroup(g_Users);
    if(!m_settings->contains(login+"/password"))
        throw std::logic_error("Wrong login or password");
    if(m_settings->value(login+"/password","") != password)
        throw std::logic_error("Wrong password");

    UserInfo info(login);
    info.isAuthorized = true;
    return info;
}
