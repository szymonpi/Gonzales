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

std::vector<std::shared_ptr<QA> > QAsSelector::select(std::vector<std::shared_ptr<QA> > qas)
{
    auto newBoundBegin = std::partition(qas.begin(), qas.end(), isOldQA);
    int maxNew = ceil(m_maxQuestions*m_newQuestionPercent);
    int maxOld = ceil(m_maxQuestions*(1-m_newQuestionPercent));

    std::vector<std::shared_ptr<QA> > oldQAs(qas.begin(),
                                             std::distance(qas.begin(), newBoundBegin) > maxOld ? qas.begin()+maxOld : newBoundBegin);

    std::vector<std::shared_ptr<QA> > newQAs(newBoundBegin,
                                             std::distance(newBoundBegin, qas.end()) > maxNew ? newBoundBegin+maxNew : qas.end());

    oldQAs.insert(oldQAs.end(),
                  std::make_move_iterator(newQAs.begin()),
                  std::make_move_iterator(newQAs.end()));
    return oldQAs;
}
