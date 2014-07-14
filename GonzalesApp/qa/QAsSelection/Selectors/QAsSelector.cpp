#include "QAsSelector.h"
#include "QAsForRepeatSelector.h"

std::vector<std::shared_ptr<QAView> > QAsSelector::select(std::vector<std::shared_ptr<QA> > &qas) const
{
    std::vector<std::shared_ptr<QAView> > selected;
    foreach(auto &selector, m_selectors)
    {
        auto currentlySelected = selector->select(qas);
        selected.insert(selected.end(), currentlySelected.begin(), currentlySelected.end());
    }
    return selected;
}
