#pragma once
#include "IQAsSelector.h"


class QAsSelector: public IQAsSelector
{
public:
    QAsSelector(std::vector<std::shared_ptr<IQAsSelector>> selectors):
        m_selectors(selectors)
    {
    }

    std::vector<std::shared_ptr<QAView> > select(std::vector<std::shared_ptr<QA> > &qas) const override;

private:
    std::vector<std::shared_ptr<IQAsSelector>> m_selectors;
};
