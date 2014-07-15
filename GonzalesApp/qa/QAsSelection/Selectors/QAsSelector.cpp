#include "QAsSelector.h"
#include "QAsForRepeatSelector.h"

std::vector<std::shared_ptr<QAView> > QAsSelector::select(std::vector<std::shared_ptr<QA> > &qas) const
{
    std::vector<std::shared_ptr<QAView> > selected;
    std::vector<std::shared_ptr<QAView>> currentlySelected = m_selectors[0]->select(qas);
    selected.insert(selected.end(), currentlySelected.begin(), currentlySelected.end());

    std::vector<std::shared_ptr<QAView>> currentlySelected2 = m_selectors[1]->select(qas);
    selected.insert(selected.end(), currentlySelected2.begin(), currentlySelected2.end());

    std::vector<std::shared_ptr<QAView>> currentlySelected3 = m_selectors[2]->select(qas);
    selected.insert(selected.end(), currentlySelected3.begin(), currentlySelected3.end());

    return selected;
}
