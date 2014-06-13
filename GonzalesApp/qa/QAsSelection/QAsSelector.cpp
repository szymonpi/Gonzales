#include "QAsSelector.h"


QAsSelector::QAsSelector(const double &newQuestionPercent, const unsigned &maxQuestion):
    m_newQuestionPercent(newQuestionPercent),
    m_maxQuestions(maxQuestion)
{

}

namespace
{

bool isOldQA(const std::shared_ptr<QA>& qa)
{
    return !qa->getAnswersHistory().empty();
}

}

QAsSelector::QAsIter QAsSelector::getNewQuestionStartIter(std::vector<std::shared_ptr<QA> > &qas)
{
    auto newBoundBegin = std::partition(qas.begin(), qas.end(), isOldQA);

    return newBoundBegin;
}

int QAsSelector::getMaxNewQasValue()
{
    int maxNew = ceil(m_maxQuestions*m_newQuestionPercent);

    return maxNew;
}

int QAsSelector::getMaxOldQAsValue()
{
    int maxOld = ceil(m_maxQuestions*(1-m_newQuestionPercent));

    return maxOld;
}

QAsSelector::QAsIter QAsSelector::getMaxNewQasIterEnd(std::vector<std::shared_ptr<QA> > &qas, QAsSelector::QAsIter newBoundBegin)
{
    int maxOld = getMaxOldQAsValue();
    return std::distance(qas.begin(), newBoundBegin) > maxOld ? qas.begin() + maxOld : newBoundBegin;
}

QAsSelector::QAsIter QAsSelector::getMaxOldQasIterEnd(std::vector<std::shared_ptr<QA> > &qas, QAsSelector::QAsIter newBoundBegin)
{
    int maxNew = getMaxNewQasValue();
    return std::distance(newBoundBegin, qas.end()) > maxNew ? newBoundBegin + maxNew : qas.end();
}

std::vector<std::shared_ptr<QA> > QAsSelector::select(std::vector<std::shared_ptr<QA> > &qas)
{
    auto newBoundBegin = getNewQuestionStartIter(qas);
    std::vector<std::shared_ptr<QA> > oldQAs(qas.begin(), getMaxNewQasIterEnd(qas, newBoundBegin));
    std::vector<std::shared_ptr<QA> > newQAs(newBoundBegin, getMaxOldQasIterEnd(qas, newBoundBegin));

    oldQAs.insert(oldQAs.end(),
                  std::make_move_iterator(newQAs.begin()),
                  std::make_move_iterator(newQAs.end()));
    return oldQAs;
}
