#pragma once
#pragma once
#include "IQAsSelector.h"
#include "../../QAToViewConverter.h"

class QAsNewSelector: public IQAsSelector
{
public:

    std::vector<std::shared_ptr<QA> > select(std::vector<std::shared_ptr<QA> > &qas) const override
    {
        auto newEnd = std::stable_partition(std::begin(qas), std::end(qas),
                                            [](const std::shared_ptr<QA>& qa)
                                            {return !qa->hasHistory();});

        std::vector<std::shared_ptr<QA>> qaViews;
        for(auto it = qas.begin(); it != newEnd; ++it)
            qaViews.push_back(*it);

        return qaViews;
    }
private:

};
