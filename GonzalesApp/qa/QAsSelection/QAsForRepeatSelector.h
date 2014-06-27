#pragma once
#include "IQAsForRepeatSelector.h"

typedef unsigned Days;

class QAsForRepeatSelector: public IQAsForRepeatSelector
{
public:
    QAsForRepeatSelector(const std::vector<Days>& repeatPeriods = std::vector<Days>{}):
       m_repeatPeriods(repeatPeriods)
    {

    }

    virtual std::vector<std::shared_ptr<QA> > select(std::vector<std::shared_ptr<QA> >& qas)
    {
        auto qaToRepeatEnd = std::stable_partition(qas.begin(), qas.end(), [](const std::shared_ptr<QA>& qa){ return qa->answerHistorySize() > 0; });
        auto qaToRepeatBegin = qas.begin();

        auto notLearnedEnd = std::stable_partition(qaToRepeatBegin, qaToRepeatEnd, [](const std::shared_ptr<QA>& qa)
        {
            auto answersHistory = qa->getAnswersHistory();
            return (--answersHistory.end())->second == QA::AnswerRating::Incorrect;
        });
        auto notLearnedBegin = qas.begin();

        return std::vector<std::shared_ptr<QA>>{notLearnedBegin, notLearnedEnd};
    }
private:
    std::vector<Days> m_repeatPeriods;

};
