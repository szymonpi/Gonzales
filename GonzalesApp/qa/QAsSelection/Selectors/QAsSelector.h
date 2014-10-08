#pragma once
#include "IQAsSelector.h"


class QAsSelector: public IQAsSelector
{
public:
    QAsSelector(std::vector<std::shared_ptr<IQAsSelector>> selectors);
    std::vector<std::shared_ptr<QA> > select(std::vector<std::shared_ptr<QA> > &qas) const override;

private:
    std::vector<std::shared_ptr<IQAsSelector>> m_selectors;
};
