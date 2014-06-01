#include "QAsSelector.h"


QAsSelector::QAsSelector(const double &newQuestionPercent, const unsigned &maxQuestion):
    m_newQuestionPercent(newQuestionPercent),
    m_maxQuestions(maxQuestion)
{

}

QVector<std::shared_ptr<QA>> QAsSelector::select(QVector<std::shared_ptr<QA>> qas)
{
    return qas;
}
