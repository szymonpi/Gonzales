#include "teacher.h"
#include <algorithm>

Teacher::Teacher(std::shared_ptr<ITextPresenter> questionPresenter,
                 std::shared_ptr<ITextPresenter> answerPresenter):
    qAToLearn(),
    lastAskedQuestion(),
    m_questionPresenter(questionPresenter),
    m_answerPresenter(answerPresenter)
{}


Teacher::Teacher(const Teacher::QAQueue &questions,
                 std::shared_ptr<ITextPresenter> questionPresenter,
                 std::shared_ptr<ITextPresenter> answerPresenter):
    qAToLearn(questions),
    allQA(questions),
    lastAskedQuestion(),
    m_questionPresenter(questionPresenter),
    m_answerPresenter(answerPresenter)
{}

void Teacher::setQuestions(const Teacher::QAQueue &questions)
{
    this->allQA = questions;
    this->qAToLearn = questions;
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
    m_answerPresenter->setText(lastAskedQuestion.qAObject().answer.getAsString());
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
    m_questionPresenter->setText(lastAskedQuestion.qAObject().question.getAsString());
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
