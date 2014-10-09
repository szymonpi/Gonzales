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

    auto oldQAsEnd = getOldQasEnd(qas.begin(), qas.end());
    auto forRepeatEnd = getRepeatQasEnd(qas.begin(), oldQAsEnd);
    auto notLearnedEnd = getNotLearnedEnd(forRepeatEnd, oldQAsEnd);

    for(auto it = qas.begin(); it != notLearnedEnd; ++it)
        selected.push_back(*it);

    auto newQasEnd = getNewQasEnd(oldQAsEnd, qas.end());
    for(auto it = oldQAsEnd; it!= newQasEnd; ++it)
        selected.push_back(*it);

    return selected;
}

QAsSelector::QAsIter QAsSelector::getRepeatQasEnd(QAsIter begin, QAsIter end) const
{
    auto forRepeatEnd = std::partition(begin, end, IsForRepeatQA{periods});
    if(std::distance(begin, forRepeatEnd) > maxForRepeat)
        forRepeatEnd = begin + maxForRepeat;
    return forRepeatEnd;
}

QAsSelector::QAsIter QAsSelector::getNotLearnedEnd(QAsIter begin, QAsIter end) const
{
    auto notLearnedEnd = std::partition(begin, end, isNotLearned{});
    if(std::distance(begin, notLearnedEnd) > maxNotLearned)
        notLearnedEnd = begin + maxNotLearned;

    return notLearnedEnd;
}

QAsSelector::QAsIter QAsSelector::getNewQasEnd(QAsIter begin, QAsIter end) const
{
    auto newQasEnd = end;
    if(std::distance(begin, end)> maxNewQAs)
        newQasEnd = begin + maxNewQAs;
    return end;
}

QAsSelector::QAsIter QAsSelector::getOldQasEnd(QAsSelector::QAsIter begin, QAsSelector::QAsIter end) const
{
    return std::partition(begin, end, isOldQA{});
}
