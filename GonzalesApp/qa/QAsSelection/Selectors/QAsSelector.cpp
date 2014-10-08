#include "QAsSelector.h"
#include "QAsForRepeatSelector.h"

QAsSelector::QAsSelector(std::vector<std::shared_ptr<IQAsSelector> > selectors):
    m_selectors(selectors)
{
}

std::vector<std::shared_ptr<QA> > QAsSelector::select(std::vector<std::shared_ptr<QA> > &qas) const
{
    std::vector<std::shared_ptr<QA> > selected;
    for(const auto& selector: m_selectors)
    {
        auto lastSelected = selector->select(qas);
        selected.insert(selected.end(), lastSelected.begin(), lastSelected.end());
    }
    return std::vector<std::shared_ptr<QA> >(selected.begin(),
                                                 selected.begin() + 10);
}
