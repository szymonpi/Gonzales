#pragma once
#include <QSettings>
#include <QVariant>
#include <QStringList>
#include "../common.h"
#include "IApplicationSettings.h"

class ApplicationSettings: public IApplicationSettings
{
public:
    ApplicationSettings():
        settings(g_Company, g_Project)
    {
    }

    QString group() override
    {
        return settings.group();
    }

    void setValue(const QString &key, const QVariant &value) override
    {
        settings.setValue(key, value);
    }

    bool contains(const QString &key)const override
    {
        return settings.contains(key);
    }

    void remove(const QString &key) override
    {
        settings.remove(key);
    }

    QVariant value(const QString &key, const QVariant &value) const override
    {
        return settings.value(key, value);
    }

    void beginGroup(const QString &str) override
    {
        settings.beginGroup(str);
    }

    QStringList childKeys() const override
    {
        return settings.childKeys();
    }

    QStringList allKeys() const override
    {
        return settings.allKeys();
    }

    QStringList childGroups() const override
    {
        return settings.childGroups();
    }

private:
    QSettings settings;
};
