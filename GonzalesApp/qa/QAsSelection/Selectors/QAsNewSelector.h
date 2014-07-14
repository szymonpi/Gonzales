#pragma once
#pragma once
#include "IQAsSelector.h"
#include "../../QAToViewConverter.h"

class QAsNewSelector: public IQAsSelector
{
public:
    QAsNewSelector(std::shared_ptr<QAToViewConverter> converter):
        m_converter(converter)
    {
    }

    std::vector<std::shared_ptr<QAView> > select(std::vector<std::shared_ptr<QA> > &qas) const override
    {
        auto newEnd = std::stable_partition(std::begin(qas), std::end(qas),
                                                  [](const std::shared_ptr<QA>& qa)
        {
            if(qa->answersHistory.empty())
                return true;
            return false;
        });
        auto newBegin = std::begin(qas);

        std::vector<std::shared_ptr<QAView>> qaViews;
        qaViews.reserve(std::distance(newBegin, newEnd));
        std::transform(newBegin, newEnd, qaViews.begin(),
                       [=](const std::shared_ptr<QA> &qa){ return m_converter->convert(qa); });
        return qaViews;
    }
private:
    std::shared_ptr<QAToViewConverter> m_converter;

};
