#pragma once
#include "IQAsSelector.h"

class QAsSelector: public IQAsSelector
{
public:
    QAsSelector(const double &newQuestionPercent, const unsigned &maxQuestion);
    QVector<std::shared_ptr<QA>> select(QVector<std::shared_ptr<QA> > qas) override;
private:
    double m_newQuestionPercent;
    unsigned m_maxQuestions;
};
