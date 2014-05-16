#ifndef IAPPLICATIONSETTINGS_H
#define IAPPLICATIONSETTINGS_H

#include <QSettings>
#include <QVariant>
#include <QStringList>

class IApplicationSettings
{
public:
    virtual void setValue(const QString &key, const QVariant &value)=0;
    virtual bool contains(const QString &key) const =0;
    virtual void remove(const QString &key)=0;
    virtual QVariant value(const QString &key, const QVariant &value) const=0;
    virtual void beginGroup(const QString &str) = 0;
    virtual QString group() = 0;
    virtual QStringList childKeys() const = 0;
    virtual QStringList allKeys() const = 0;
    virtual QStringList childGroups() const = 0;
};


#endif // IAPPLICATIONSETTINGS_H
