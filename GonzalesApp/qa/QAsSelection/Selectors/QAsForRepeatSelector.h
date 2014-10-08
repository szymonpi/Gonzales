#pragma once
#include "IQAsSelector.h"
#include "Utils/IQARepeatPeriodChecker.h"
#include "../../QAToSimpleViewConverter.h"


class QAsForRepeatSelector: public IQAsSelector
{
public:
    QAsForRepeatSelector(std::shared_ptr<IQARepeatPeriodChecker> toRepeatSelector):
        m_toRepeatSelector(toRepeatSelector)
    {
    }

    std::vector<std::shared_ptr<QA> > select(std::vector<std::shared_ptr<QA> >& qas) const override;

private:
    std::shared_ptr<IQARepeatPeriodChecker> m_toRepeatSelector;
};
