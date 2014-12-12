#pragma once
#include "ISetting.h"


template <class T>
class Setting: public ISetting
{
public:
    Setting(std::function<T()> getter,
            std::function<void(const T&)> uiSetter,
            std::function<void(const T&)> settingsUserSetter,
            std::shared_ptr<IApplicationSettings> applicationSettings,
            const QString& pathToSettings,
            const QString& name,
            T defaultVal):
        getter(getter),
        uiSetter(uiSetter),
        settingsUserSetter(settingsUserSetter),
        applicationSettings(applicationSettings),
        pathToSettings(pathToSettings),
        name(name),
        defaultVal(defaultVal)
    {
    }

    void update() override
    {
        T currentValue = getter();
        applicationSettings->setValue(pathToSettings + "/" + name, currentValue);
        settingsUserSetter(currentValue);
    }

    void load() override
    {
        QVariant val = applicationSettings->value(pathToSettings + "/" + name, defaultVal);
        uiSetter(val.value<T>());
        settingsUserSetter(val.value<T>());
    }

private:
    std::function<T()> getter;
    std::function<void(const T&)> uiSetter;
    std::function<void(const T&)> settingsUserSetter;
    std::shared_ptr<IApplicationSettings> applicationSettings;
    QString pathToSettings;
    QString name;
    T defaultVal;
};
