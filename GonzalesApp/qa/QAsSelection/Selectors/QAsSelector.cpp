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
    int i = std::distance(oldQAsEnd, newQasEnd);
    i = i* 5;
    for(auto it = oldQAsEnd; it!= newQasEnd; ++it)
        selected.push_back(*it);

    return selected;
}

void QAsSelector::setMaxQA(QAsSelector::Settings settings, unsigned qaNumber)
{
    qaMax[settings] = qaNumber;
}

void QAsSelector::setPeriods(std::vector<Day> newPeriods)
{
    periods.clear();
    periods.insert(newPeriods.begin(), newPeriods.end());
}

QAsSelector::QAsIter QAsSelector::getRepeatQasEnd(QAsIter begin, QAsIter end) const
{
    auto forRepeatEnd = std::partition(begin, end, IsForRepeatQA{periods});
    int dist = std::distance(begin, forRepeatEnd);
    if( dist> qaMax.at(SettingsMaxForRepeat))
        forRepeatEnd = begin + qaMax.at(SettingsMaxForRepeat);
    return forRepeatEnd;
}

QAsSelector::QAsIter QAsSelector::getNotLearnedEnd(QAsIter begin, QAsIter end) const
{
    auto notLearnedEnd = std::partition(begin, end, isNotLearned{});
    if(std::distance(begin, notLearnedEnd) > qaMax.at(SettingsMaxNotLearned))
        notLearnedEnd = begin + qaMax.at(SettingsMaxNotLearned);

    return notLearnedEnd;
}

QAsSelector::QAsIter QAsSelector::getNewQasEnd(const QAsIter begin, QAsIter end) const
{
    auto newQasEnd = end;
    if(std::distance(begin, end)> qaMax.at(SettingsMaxNewQAs))
        newQasEnd = begin + qaMax.at(SettingsMaxNewQAs);
    return newQasEnd;
}

QAsSelector::QAsIter QAsSelector::getOldQasEnd(QAsSelector::QAsIter begin, QAsSelector::QAsIter end) const
{
    return std::partition(begin, end, isOldQA{});
}
