#include "Teacher.h"
#include <algorithm>
#include "../qa/QASimpleView.h"

Teacher::Teacher(std::shared_ptr<IQAsToLearnProvider> qAsToLearnProvider):
    lastAskedQuestion()
{
    m_qAViewsToLearn = qAsToLearnProvider->getQAs();

    if(m_qAViewsToLearn.empty())
        throw std::logic_error("Did you check what you want to learn?");

}

void Teacher::markAsUnknown()
{
    lastAskedQuestion->markAsUnknown();
    addWrongAnsweredQAToQueue();
}

void Teacher::markAsKnown()
{
    lastAskedQuestion->markAsKnown();
    removeCurrentAskedQA();
}

void Teacher::showCorrectAnswer() const
{
    lastAskedQuestion->presentAnswer();
}

int Teacher::questionsToLearnNum() const
{
    return m_qAViewsToLearn.size();
}

void Teacher::showNextQuestion()
{
    checkIsQaQueueEmpty();
    moveCurrentQuestionToAsked();
    lastAskedQuestion->presentQuestion();
}

void Teacher::removeCurrentAskedQA()
{
    lastAskedQuestion.reset();
}

void Teacher::addWrongAnsweredQAToQueue()
{
    m_qAViewsToLearn.push_back(lastAskedQuestion);
    lastAskedQuestion.reset();
}

void Teacher::checkIsQaQueueEmpty()
{
    if(m_qAViewsToLearn.empty())
        throw std::logic_error("empty questions container");
}

void Teacher::moveCurrentQuestionToAsked()
{
    lastAskedQuestion = m_qAViewsToLearn.front();
    m_qAViewsToLearn.pop_front();
}
