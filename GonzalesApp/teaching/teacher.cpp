#include "teacher.h"
#include <algorithm>

Teacher::Teacher(std::shared_ptr<IQuestionPresenter> questionPresenter,
                 std::shared_ptr<IAnswerPresenter> answerPresenter,
                 std::shared_ptr<IQAsToLearnProvider> qAsToLearnProvider,
                 std::shared_ptr<IQAMarker> qaMarker):
    lastAskedQuestion(),
    m_questionPresenter(questionPresenter),
    m_answerPresenter(answerPresenter),
    m_qaMarker(qaMarker),
    m_qAsToLearn(qAsToLearnProvider->getQAs())
{
    if(m_qAsToLearn.empty())
        throw std::logic_error("Are you check what you want to learn?");
}

void Teacher::markAsUnknown()
{
    m_qaMarker->markAsUnknown(*lastAskedQuestion);
    addWrongAnsweredQAToQueue();
}

void Teacher::markAsKnown()
{
    m_qaMarker->markAsKnown(*lastAskedQuestion);
    removeCurrentAskedQA();
}

void Teacher::showCorrectAnswer() const
{
    m_answerPresenter->presentAnswer(lastAskedQuestion->getAnswer());
}

int Teacher::questionsToLearnNum() const
{
    return m_qAsToLearn.size();
}

void Teacher::showNextQuestion()
{
    checkIsQaQueueEmpty();
    moveCurrentQuestionToAsked();
    m_answerPresenter->clear();
    m_questionPresenter->presentQuestion(lastAskedQuestion->getQuestion());
}

void Teacher::removeCurrentAskedQA()
{
    lastAskedQuestion.reset();
}

void Teacher::addWrongAnsweredQAToQueue()
{
    m_qAsToLearn.push_back(lastAskedQuestion);
    lastAskedQuestion.reset();
}

void Teacher::checkIsQaQueueEmpty()
{
    if(m_qAsToLearn.empty())
        throw std::logic_error("empty questions container");
}

void Teacher::moveCurrentQuestionToAsked()
{
    lastAskedQuestion = m_qAsToLearn.front();
    m_qAsToLearn.pop_front();
}
