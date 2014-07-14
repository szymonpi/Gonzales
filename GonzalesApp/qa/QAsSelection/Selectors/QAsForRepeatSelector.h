#pragma once
#include "IQAsSelector.h"
#include "Utils/QARepeatPeriodChecker.h"
#include "../../QAToSimpleViewConverter.h"


class QAsForRepeatSelector: public IQAsSelector
{
public:
    QAsForRepeatSelector(std::shared_ptr<QAToViewConverter> converter):
        m_converter(converter)
    {
    }

    std::vector<std::shared_ptr<QAView> > select(std::vector<std::shared_ptr<QA> >& qas) const override
    {

        std::vector<std::shared_ptr<QAView>> toRepeat{};

        std::set<Day> periods{1,2,4,7,14,30,90,180,360};
        QARepeatPeriodChecker selector{periods};

        for(auto it = qas.begin(); it != qas.end(); ++it)
        {
            if(selector.ShouldBeRepeated((*it)->answersHistory))
                toRepeat.push_back(m_converter->convert(*it));
        }

        return toRepeat;
    }

private:
    std::shared_ptr<QAToViewConverter> m_converter;

};
