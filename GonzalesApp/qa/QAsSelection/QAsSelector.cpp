#include "QAsSelector.h"


QAsSelector::QAsSelector(const double &newQuestionPercent, const unsigned &maxQuestion):
    m_newQuestionPercent(newQuestionPercent),
    m_maxQuestions(maxQuestion)
{

}

std::vector<std::shared_ptr<QA>> QAsSelector::select(std::vector<std::shared_ptr<QA>> qas)
{

}
