#include "Teacher.h"
#include <algorithm>
#include "../qa/QASimpleView.h"

Teacher::Teacher(std::shared_ptr<IQuestionPresenter> questionPresenter,
                 std::shared_ptr<IAnswerPresenter> answerPresenter,
                 std::shared_ptr<IQAsToLearnProvider> qAsToLearnProvider,
                 std::shared_ptr<IQAMarker> qaMarker):
    lastAskedQuestion(),
    m_questionPresenter(questionPresenter),
    m_answerPresenter(answerPresenter),
    m_qaMarker(qaMarker)
{
    auto qasData = qAsToLearnProvider->getQAs();
    std::for_each(qasData.begin(), qasData.end(),
                  [=](std::shared_ptr<QA> &qa)
    { m_qAViewsToLearn.push_back(std::make_shared<QASimpleView>(m_questionPresenter, m_answerPresenter, m_qaMarker, qa)); });

    if(m_qAViewsToLearn.empty())
        throw std::logic_error("Are you check what you want to learn?");

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
    m_answerPresenter->clear();
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
