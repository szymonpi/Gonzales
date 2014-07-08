#pragma once
#include "IQAsForRepeatSelector.h"
#include "QARepeatPeriodChecker.h"


class QAsForRepeatSelector: public IQAsForRepeatSelector
{
public:

    virtual std::vector<std::shared_ptr<QA> > select(std::vector<std::shared_ptr<QA> > qas)
    {
        auto qasWithHistoryEnd = std::stable_partition(qas.begin(), qas.end(), [](const std::shared_ptr<QA>& qa){ return qa->answerHistorySize() > 0; });
        auto qasWithHistoryBegin = qas.begin();

        auto notLearnedEnd = std::stable_partition(qasWithHistoryBegin, qasWithHistoryEnd, [](const std::shared_ptr<QA>& qa)
        {
            auto answersHistory = qa->getAnswersHistory();
            return (--answersHistory.end())->second == QA::AnswerRating::Incorrect;
        });
        auto notLearnedBegin = begin(qas);


        auto learnedEnd = std::stable_partition(qasWithHistoryBegin, qasWithHistoryEnd, [](const std::shared_ptr<QA>& qa)
        {
            auto answersHistory = qa->getAnswersHistory();
            return (--answersHistory.end())->second == QA::AnswerRating::Incorrect;
        });
        auto learnedBegin = begin(qas);

        std::vector<std::shared_ptr<QA>> learned{learnedBegin, learnedEnd};

        std::vector<std::shared_ptr<QA>> notLearned{notLearnedBegin, notLearnedEnd};
        std::vector<std::shared_ptr<QA>> toRepeat{};


        std::set<Day> periods{1,2,4,7,14,30,90,180,360};
        QARepeatPeriodChecker selector{periods};

        foreach(const auto& qa, learned)
        {
            if(selector.ShouldBeRepeated(qa->answersHistory))
                toRepeat.push_back(qa);
        }

        std::vector<std::shared_ptr<QA>> allToLearn{notLearned};
        allToLearn.insert(allToLearn.end(), toRepeat.end(), toRepeat.end());

        return allToLearn;
    }

};
