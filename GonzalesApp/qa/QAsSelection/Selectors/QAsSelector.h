#pragma once
#include "IQAsSelector.h"
#include "Utils/QARepeatPeriodChecker.h"
#include "QAsNewSelector.h"
#include "QAsNotLearnedSelector.h"
#include "IQASelectorSettings.h"

class QAsSelector: public IQAsSelector,
                   public IQASelectorSettings
{
public:

    typedef std::vector<std::shared_ptr<QA> >::iterator QAsIter;

    std::vector<std::shared_ptr<QA> > select(std::vector<std::shared_ptr<QA> > &qas) const override;
    void setMaxQA(Settings settings, unsigned qaNumber);
    void setPeriods(std::vector<Day> newPeriods);


private:
    QAsIter getOldQasEnd(QAsIter begin, QAsIter end) const;
    QAsSelector::QAsIter getRepeatQasEnd(QAsIter begin, QAsIter end) const;
    QAsSelector::QAsIter getNotLearnedEnd(QAsIter begin, QAsIter end) const;
    QAsSelector::QAsIter getNewQasEnd(QAsIter begin, QAsIter end) const;

    std::map<Settings, Day> qaMax{{SettingsMaxForRepeat, 20},
                                       {SettingsMaxNewQAs, 15},
                                       {SettingsMaxNotLearned, 20}};
    std::set<Day> periods{1,2,7,30,90,180,360};
};
