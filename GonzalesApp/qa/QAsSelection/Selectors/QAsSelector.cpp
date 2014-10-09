#include "QAsSelector.h"

class isOldQA: public std::unary_function<const std::shared_ptr<QA>&, bool>
{
public:
    bool operator()(const std::shared_ptr<QA>& qa)
    {
        return qa->hasHistory();
    }
};


std::vector<std::shared_ptr<QA> > QAsSelector::select(std::vector<std::shared_ptr<QA> > &qas) const
{
    std::vector<std::shared_ptr<QA> > selected;

    auto oldQAsEnd = std::partition(qas.begin(), qas.end(), isOldQA{});

    auto forRepeatEnd = std::partition(qas.begin(), oldQAsEnd, IsForRepeatQA{{1,2,7,30,90,180,360}});

    int maxForRepeat{10};

    if(std::distance(qas.begin(), forRepeatEnd) > maxForRepeat)
        forRepeatEnd = qas.begin() + maxForRepeat;

    auto notLearnedEnd = std::partition(forRepeatEnd, oldQAsEnd, isNotLearned{});
    for(auto it = qas.begin(); it != notLearnedEnd; ++it)
        selected.push_back(*it);

    int maxNewQAs = 10;

    auto newQasEnd = qas.end();
    if(std::distance(oldQAsEnd, qas.end())> maxNewQAs)
        newQasEnd = oldQAsEnd + maxNewQAs;

    for(auto it = oldQAsEnd; it!= newQasEnd; ++it)
        selected.push_back(*it);

    return selected;
}
