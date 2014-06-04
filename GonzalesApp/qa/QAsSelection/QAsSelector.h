#pragma once
#include "IQAsSelector.h"

class QAsSelector: public IQAsSelector
{
public:
    typedef std::vector<std::shared_ptr<QA> >::iterator QAsIter;
    QAsSelector(const double &newQuestionPercent, const unsigned &maxQuestion);
    std::vector<std::shared_ptr<QA> > select(std::vector<std::shared_ptr<QA> > &qas) override;

private:
    int getMaxNewQasValue();
    int getMaxOldQAsValue();
    QAsIter getMaxNewQasIterEnd(std::vector<std::shared_ptr<QA> > &qas, QAsSelector::QAsIter newBoundBegin);
    QAsIter getMaxOldQasIterEnd(std::vector<std::shared_ptr<QA> > &qas, QAsSelector::QAsIter newBoundBegin);

    QAsIter getNewQuestionStartIter(std::vector<std::shared_ptr<QA> > &qas);

    double m_newQuestionPercent;
    unsigned m_maxQuestions;
};
