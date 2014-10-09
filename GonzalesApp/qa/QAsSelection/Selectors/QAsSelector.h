#pragma once
#include "IQAsSelector.h"
#include "Utils/QARepeatPeriodChecker.h"
#include "QAsNewSelector.h"
#include "QAsNotLearnedSelector.h"

class QAsSelector: public IQAsSelector
{
public:
    std::vector<std::shared_ptr<QA> > select(std::vector<std::shared_ptr<QA> > &qas) const override;

};
