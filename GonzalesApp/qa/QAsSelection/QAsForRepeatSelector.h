#pragma once
#include "IQAsForRepeatSelector.h"



bool isAnyRepatingPeriodInQA(const std::shared_ptr<QA>& qa)
{
    auto itemSinceThereWasntBadAnswer = qa->answersHistory.rbegin();

    for(auto it = qa->answersHistory.rbegin(); it != qa->answersHistory.rend(); ++it)
    {
        if(it->second == QA::AnswerRating::Incorrect)
            break;
        itemSinceThereWasntBadAnswer = it;
    }
    return false;
}

class QAsForRepeatSelector: public IQAsForRepeatSelector
{
public:

    virtual std::vector<std::shared_ptr<QA> > select(std::vector<std::shared_ptr<QA> >& qas)
    {
        auto qaToRepeatEnd = std::stable_partition(qas.begin(), qas.end(), [](const std::shared_ptr<QA>& qa){ return qa->answerHistorySize() > 0; });
        auto qaToRepeatBegin = qas.begin();

        auto learnedEnd = std::stable_partition(qaToRepeatBegin, qaToRepeatEnd, [](const std::shared_ptr<QA>& qa)
        {
            auto answersHistory = qa->getAnswersHistory();
            return (--answersHistory.end())->second == QA::AnswerRating::Correct;
        });
        auto learnedBegin = std::begin(qas);


        learnedBegin = begin(qas);

        std::vector<std::shared_ptr<QA>> vector{learnedBegin, learnedEnd};

        return vector;
    }

};
