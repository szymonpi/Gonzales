#pragma once
#include <vector>

class IQASelectorSettings
{
public:
    enum Settings
    {
        SettingsMaxForRepeat,
        SettingsMaxNewQAs,
        SettingsMaxNotLearned,
    };

    virtual ~IQASelectorSettings(){}
    virtual void setMaxQA(Settings settings, unsigned qaNumber) = 0;
    virtual void setPeriods(std::vector<Day> newPeriods) = 0;
};
