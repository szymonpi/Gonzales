#include "Authorizer.h"
#include "../common/Encryptors.h"




UserInfo Authorizer::authorize(const QString &login, const QString &password)
{
    m_settings->beginGroup(g_Users);
    if(!m_settings->contains(login+"/password"))
        throw std::logic_error("Wrong login or password");

    PasswordEncryptor encryptor;
    QString encryptedPassword = encryptor.encrypt(password,
                                                  m_settings->value(login+"/passwordSalt","").toString());
    QString savedEncryptedPassword = m_settings->value(login+"/password","").toString();
    if(savedEncryptedPassword != encryptedPassword)
        throw std::logic_error("Wrong password");

    UserInfo info(login);
    info.isAuthorized = true;
    return info;
}
