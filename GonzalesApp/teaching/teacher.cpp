#include "teacher.h"
#include <algorithm>

Teacher::Teacher(std::shared_ptr<IQuestionPresenter> questionPresenter,
                 std::shared_ptr<IAnswerPresenter> answerPresenter,
                 std::shared_ptr<QasProvider> qAsProvider):
    qAToLearn(),
    lastAskedQuestion(),
    m_questionPresenter(questionPresenter),
    m_answerPresenter(answerPresenter),
    m_qAsProvider(qAsProvider)
{
    std::vector<QA> l_qas = m_qAsProvider->getQAs();
    std::copy(l_qas.begin(), l_qas.end(), std::back_inserter(allQA));
    qAToLearn = allQA;
}

void Teacher::setQuestions(const std::vector<QA> &questions)
{
    std::vector<QA> l_qas = questions;
    std::copy(l_qas.begin(), l_qas.end(), std::back_inserter(allQA));
    qAToLearn = allQA;
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
    m_answerPresenter->presentAnswer(lastAskedQuestion.qAObject().answer);
}

int Teacher::questionsToLearnNum() const
{
    return qAToLearn.size();
}

void Teacher::showNextQuestion()
{
    checkIsQaQueueEmpty();
    moveCurrentQuestionToAsked();
    m_answerPresenter->clear();
    m_questionPresenter->presentQuestion(lastAskedQuestion.qAObject().question);
}

void Teacher::removeCurrentAskedQA()
{
    lastAskedQuestion.removeQuestion();
}

void Teacher::addWrongAnsweredQAToQueue()
{
    qAToLearn.push_back(lastAskedQuestion.qAObject());
    lastAskedQuestion.removeQuestion();
}

void Teacher::checkIsQaQueueEmpty()
{
    if(qAToLearn.empty())
        throw std::logic_error("empty questions container");
}

void Teacher::moveCurrentQuestionToAsked()
{
    lastAskedQuestion.setQA(qAToLearn.front());
    qAToLearn.pop_front();
}
