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

    std::vector<std::shared_ptr<QAView> > select(std::vector<std::shared_ptr<QA> > &qas) const override
    {
        auto notLearnedEnd = std::stable_partition(std::begin(qas), std::end(qas),
                                                  [](const std::shared_ptr<QA>& qa)
        {
            if(qa->answersHistory.empty())
                return false;
            auto &aH = qa->answersHistory;
            return (--aH.end())->second == QA::AnswerRating::Incorrect;
        });
        auto notLearnedBegin = std::begin(qas);

        std::vector<std::shared_ptr<QAView>> qaViews;
        std::transform(notLearnedBegin, notLearnedEnd, qaViews.begin(),
                       [&](const std::shared_ptr<QA> &qa){ return m_converter->convert(qa); });
        return qaViews;
    }
private:
    std::shared_ptr<QAToViewConverter> m_converter;

};
