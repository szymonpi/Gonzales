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
        std::vector<std::shared_ptr<QAView>> qaViews{};

        if(newEnd == qas.end())
            return qaViews;
        auto newBegin = std::begin(qas);
        for(auto it = newBegin; it != newEnd; ++it)
        {
            qaViews.push_back(m_converter->convert(*it));
        }
        return qaViews;
    }
private:
    std::shared_ptr<QAToViewConverter> m_converter;

};
