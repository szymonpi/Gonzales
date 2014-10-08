#include "QAsForRepeatSelector.h"



std::vector<std::shared_ptr<QA> > QAsForRepeatSelector::select(std::vector<std::shared_ptr<QA> > &qas) const
{

    std::vector<std::shared_ptr<QA>> toRepeat;

    for(auto it = qas.begin(); it != qas.end(); ++it)
    {
        if(m_toRepeatSelector->shouldBeRepeated((*it)->answersHistory))
            toRepeat.push_back(*it);
    }

    return toRepeat;
}
