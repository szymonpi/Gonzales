#include "teacher.h"
#include <algorithm>

Teacher::Teacher(std::shared_ptr<IQuestionPresenter> questionPresenter,
                 std::shared_ptr<IAnswerPresenter> answerPresenter,
                 std::shared_ptr<IQAsToLearnProvider> qAsToLearnProvider):
    lastAskedQuestion(),
    m_questionPresenter(questionPresenter),
    m_answerPresenter(answerPresenter),
    m_qAsToLearn(qAsToLearnProvider->getQAs())
{
    if(m_qAsToLearn.empty())
        throw std::logic_error("Are you check what you want to learn?");
}

void Teacher::markAsUnknown()
{
    addWrongAnsweredQAToQueue();
}

void Teacher::markAsKnown()
{
    removeCurrentAskedQA();
}

void Teacher::showCorrectAnswer() const
{
    m_answerPresenter->presentAnswer(lastAskedQuestion->answer);
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
    m_questionPresenter->presentQuestion(lastAskedQuestion->question);
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
