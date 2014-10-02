#include "QAsSelector.h"
#include "QAsForRepeatSelector.h"

std::vector<std::shared_ptr<QAView> > QAsSelector::select(std::vector<std::shared_ptr<QA> > &qas) const
{
    std::vector<std::shared_ptr<QAView> > selected;
    for(const auto& selector: m_selectors)
    {
        auto lastSelected = selector->select(qas);
        selected.insert(selected.end(), lastSelected.begin(), lastSelected.end());
    }
    return std::vector<std::shared_ptr<QAView> >(selected.begin(),
                                                 selected.begin() + 10);
}
