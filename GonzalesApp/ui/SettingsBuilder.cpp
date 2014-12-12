#include "SettingsBuilder.h"
#include "../qa/QAsSelection/Selectors/MaterialDisposalCalculator.h"
#include "../qa/QAsSelection/Selectors/QAsSelector.h"
#include <functional>

SettingsBuilder::SettingsBuilder(const QString& settingsPath,
                                 std::unique_ptr<IApplicationSettings> applicationSettings):
    settingsPath(settingsPath),
    applicationSettings(std::move(applicationSettings))
{
}

std::vector<std::shared_ptr<ISetting> > SettingsBuilder::build(Ui::MainWindow &ui,
                                                               std::shared_ptr<IQASelectorSettings> selectorSettings)
{
    std::vector<std::shared_ptr<ISetting>> settings;

    settings.push_back(buildMaterialDisposal(ui, selectorSettings));
    settings.push_back(buildMaterialAmount(ui, selectorSettings));
    settings.push_back(buildPeriodsList(ui, selectorSettings));

   return settings;
}

std::shared_ptr<ISetting> SettingsBuilder::buildMaterialDisposal(Ui::MainWindow &ui,
                                                                 std::shared_ptr<IQASelectorSettings> selectorSettings)
{
    std::function<int(void)> getterFun = [&](){ return ui.horizontalSlider->value();};
    std::function<void(const int&)> uiSetterFun = [&](const int& val){ ui.horizontalSlider->setValue(val);};
    std::function<void(const int&)> userSetter = [selectorSettings, &ui](const int& val)
    {
       MaterialDisposalCalculator calc{ui.spinBoxMaterialAmount->value(), val};
       selectorSettings->setMaxQA(QAsSelector::SettingsMaxNewQAs, calc.maxNew());
       selectorSettings->setMaxQA(QAsSelector::SettingsMaxForRepeat, calc.maxForRepetition());
       selectorSettings->setMaxQA(QAsSelector::SettingsMaxNotLearned, calc.maxNotLearned());
    };

    std::shared_ptr<ISetting> setting = std::make_shared<Setting<int> >
    (
        getterFun,
        uiSetterFun,
        userSetter,
        applicationSettings,
        settingsPath,
        "MaterialDisposal",
        30
    );

    return setting;
}

std::shared_ptr<ISetting> SettingsBuilder::buildMaterialAmount(Ui::MainWindow &ui,
                                                               std::shared_ptr<IQASelectorSettings> selectorSettings)
{

   auto getterFun = [&ui](){ return ui.spinBoxMaterialAmount->value();};
   auto uiSetterFun = [&ui](const int& val){ ui.spinBoxMaterialAmount->setValue(val);};
   auto userSetter = [selectorSettings, &ui](const int& val)
   {
      MaterialDisposalCalculator calc{val, ui.horizontalSlider->value()};
      selectorSettings->setMaxQA(QAsSelector::SettingsMaxNewQAs, calc.maxNew());
      selectorSettings->setMaxQA(QAsSelector::SettingsMaxForRepeat, calc.maxForRepetition());
      selectorSettings->setMaxQA(QAsSelector::SettingsMaxNotLearned, calc.maxNotLearned());
   };

   std::shared_ptr<ISetting> setting = std::make_shared<Setting<int> >
   (
       getterFun,
       uiSetterFun,
       userSetter,
       applicationSettings,
       settingsPath,
       "MaterialAmount",
       30
   );

   return setting;
}

std::shared_ptr<ISetting> SettingsBuilder::buildPeriodsList(Ui::MainWindow &ui,
                                                            std::shared_ptr<IQASelectorSettings> selectorSettings)
{
    auto getterFun = [&]()
    {
        QStringList items;
        for(int i = 0; i < ui.listWidgetRepetitionPeriods->count(); ++i)
            {
                items.push_back(ui.listWidgetRepetitionPeriods->item(i)->text());
            }
        return items;
    };

    auto uiSetterFun = [&](const QStringList& val)
                       {ui.listWidgetRepetitionPeriods->clear();
                        ui.listWidgetRepetitionPeriods->addItems(val);};
    auto userSetter = [=](const QStringList& val)
    {
        std::vector<Day> periods;
        std::transform(val.begin(), val.end(),
                       std::back_inserter(periods),
                       [](const QString& s){ return s.toUInt();});
        selectorSettings->setPeriods(periods);
    };
    std::shared_ptr<ISetting> setting = std::make_shared<Setting<QStringList> >
    (
        getterFun,
        uiSetterFun,
        userSetter,
        applicationSettings,
        settingsPath,
        "Periods",
        QStringList() << "1" << "2" << "7" << "30" << "90" << "180" << "360"
    );

    return setting;
}
