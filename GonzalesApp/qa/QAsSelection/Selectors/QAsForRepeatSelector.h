#pragma once
#include "IQAsSelector.h"
#include "Utils/IQARepeatPeriodChecker.h"
#include "../../QAToSimpleViewConverter.h"


class QAsForRepeatSelector: public IQAsSelector
{
public:
    QAsForRepeatSelector(std::shared_ptr<QAToViewConverter> converter,
                         std::shared_ptr<IQARepeatPeriodChecker> toRepeatSelector):
        m_converter(converter),
        m_toRepeatSelector(toRepeatSelector)
    {
    }

    std::vector<std::shared_ptr<QAView> > select(std::vector<std::shared_ptr<QA> >& qas) const override;

private:
    std::shared_ptr<QAToViewConverter> m_converter;
    std::shared_ptr<IQARepeatPeriodChecker> m_toRepeatSelector;
};
