#pragma once
#include "IQAsSelector.h"
#include "../../QAToViewConverter.h"

class QAsNotLearnedSelector: public IQAsSelector
{
public:
    QAsNotLearnedSelector(std::shared_ptr<QAToViewConverter> converter):
        m_converter(converter)
    {
    }

    std::vector<std::shared_ptr<QAView> > convertQAs(std::vector<std::shared_ptr<QA> >::iterator begin,
                                                     std::vector<std::shared_ptr<QA> >::iterator end) const
    {
        std::vector<std::shared_ptr<QAView>> qaViews;
        for(auto it = begin; it != end; ++it)
            qaViews.push_back(m_converter->convert(*it));

        return qaViews;
    }

    std::vector<std::shared_ptr<QA> >::iterator notNewNotLearnedStablePartition(std::vector<std::shared_ptr<QA> > &qas) const
    {
        auto notLearnedEnd = std::stable_partition(std::begin(qas), std::end(qas),
                                                  [](const std::shared_ptr<QA>& qa)
        {
            if(qa->answersHistory.empty())
                return false;
            auto &aH = qa->answersHistory;
            return (--aH.end())->second == QA::AnswerRating::Incorrect;
        });

        return notLearnedEnd;
    }

    std::vector<std::shared_ptr<QAView> > select(std::vector<std::shared_ptr<QA> > &qas) const override
    {
        return convertQAs(qas.begin(), notNewNotLearnedStablePartition(qas));
    }
private:
    std::shared_ptr<QAToViewConverter> m_converter;

};
