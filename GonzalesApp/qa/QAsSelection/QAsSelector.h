#pragma once
#include "IQAsSelector.h"

class QAsSelector: public IQAsSelector
{
public:
    QAsSelector(const double &newQuestionPercent, const unsigned &maxQuestion);
    std::vector<std::shared_ptr<QA> > select(std::vector<std::shared_ptr<QA> > qas) override;
private:
    double m_newQuestionPercent;
    unsigned m_maxQuestions;
};
