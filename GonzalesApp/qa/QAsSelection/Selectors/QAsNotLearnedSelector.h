#pragma once
#include "IQAsSelector.h"
#include "../../QAToViewConverter.h"

class QAsNotLearnedSelector: public IQAsSelector
{
public:
    std::vector<std::shared_ptr<QA> > convertQAs(std::vector<std::shared_ptr<QA> >::iterator begin,
                                                     std::vector<std::shared_ptr<QA> >::iterator end) const
    {
        std::vector<std::shared_ptr<QA>> qas;
        for(auto it = begin; it != end; ++it)
            qas.push_back(*it);

        return qas;
    }

    std::vector<std::shared_ptr<QA> >::iterator notNewNotLearnedStablePartition(std::vector<std::shared_ptr<QA> > &qas) const
    {
        auto notLearnedEnd = std::stable_partition(std::begin(qas), std::end(qas),
                                                  [](const std::shared_ptr<QA>& qa)
        {
            if(qa->answersHistory.empty())
                return false;
            return (--qa->answersHistory.end())->second == QA::AnswerRating::Incorrect;
        });

        return notLearnedEnd;
    }

    std::vector<std::shared_ptr<QA> > select(std::vector<std::shared_ptr<QA> > &qas) const override
    {
        return convertQAs(qas.begin(), notNewNotLearnedStablePartition(qas));
    }
private:
    std::shared_ptr<QAToViewConverter> m_converter;

};
