#pragma once
#include <QtGlobal>
#include <QCryptographicHash>
#include <QString>

class SaltGenerator
{
public:
    QString generate(int length)
    {
        QString generated;
        generated.reserve(length);
        for(int i=0; i<length; i++)
        {
            int random = qrand() % possibleCharacters.size();
            generated.append(possibleCharacters.at(random));
        }
        return generated;
    }

    const QString possibleCharacters = {"`1234567890-=qwertyuiop[]\asdfghjkl;'zxcvbnm,./~!@#$%^&*()_+QWERTYUIOP{}|ASDFGHJKL:\"ZXCVBNM<>?"};
};

struct PasswordInfo
{
    QString encryptedPassword;
    QString salt;
};

class SimpleEncryptor
{
public:
    QString encrypt(const QString& string)
    {
        return QString(QCryptographicHash::hash(string.toUtf8(), QCryptographicHash::Md5));
    }
};

class PasswordEncryptor
{
public:
    PasswordInfo encrypt(const QString& password)
    {
        PasswordInfo info;
        info.salt = saltGen.generate(20);
        info.encryptedPassword = encryptor.encrypt(password+info.salt);
        return info;
    }

    QString encrypt(const QString& password, const QString& salt)
    {
        return encryptor.encrypt(password+salt);
    }

    SimpleEncryptor encryptor;
    SaltGenerator saltGen;
};
