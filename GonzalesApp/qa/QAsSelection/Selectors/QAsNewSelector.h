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
                                            {return qa->answersHistory.empty();});

        std::vector<std::shared_ptr<QAView>> qaViews;
        for(auto it = qas.begin(); it != newEnd; ++it)
            qaViews.push_back(m_converter->convert(*it));

        return qaViews;
    }
private:
    std::shared_ptr<QAToViewConverter> m_converter;

};
