#pragma once
#include <memory>

#include "ui_mainwindow.h"
#include "../common/Setting.h"
#include "../qa/QAsSelection/Selectors/IQASelectorSettings.h"
#include "../User/UserInfo.h"
#include "../common/qtproxies/ApplicationSettings.h"

class SettingsBuilder
{
public:
    SettingsBuilder(const QString& settingsPath,
                    std::unique_ptr<IApplicationSettings> applicationSettings =
            std::unique_ptr<ApplicationSettings>(new ApplicationSettings()));

    std::vector<std::shared_ptr<ISetting> > build(Ui::MainWindow &ui, std::shared_ptr<IQASelectorSettings> selectorSettings);

private:
    const QString settingsPath;
    std::shared_ptr<IApplicationSettings> applicationSettings;

    std::shared_ptr<ISetting> buildMaterialDisposal(Ui::MainWindow &ui, std::shared_ptr<IQASelectorSettings> selectorSettings);
    std::shared_ptr<ISetting> buildMaterialAmount(Ui::MainWindow &ui, std::shared_ptr<IQASelectorSettings> selectorSettings);
    std::shared_ptr<ISetting> buildPeriodsList(Ui::MainWindow &ui, std::shared_ptr<IQASelectorSettings> selectorSettings);
};

