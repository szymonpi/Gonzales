#include "teacher.h"

Teacher::Teacher():
    qAqueue(),
    lastAskedQuestion()
{
}


Teacher::Teacher(const Teacher::QAQueue &questions):
    qAqueue(questions),
    lastAskedQuestion()
{
}

void Teacher::setQuestions(const Teacher::QAQueue &questions)
{
    this->qAqueue = questions;
}

bool Teacher::checkAnswer(const Answer &answer)
{
    if(isCurrentAnswerCorrect(Answer(answer)))
        removeCurrentAskedQA();
    else
    {
        addWrongAnsweredQAToQueue();
        return false;
    }
    return true;
}

Question Teacher::getNextQuestion()
{
    checkIsQaQueueEmpty();
    moveCurrentQuestionToAsked();
    return lastAskedQuestion.qAObject().question;
}

bool Teacher::isCurrentAnswerCorrect(const Answer &answer)
{
    QAPair currentQA = lastAskedQuestion.qAObject();
    return currentQA.answer == answer;
}

void Teacher::removeCurrentAskedQA()
{
    lastAskedQuestion.removeQuestion();
}

void Teacher::addWrongAnsweredQAToQueue()
{
    qAqueue.push(lastAskedQuestion.qAObject());
    lastAskedQuestion.removeQuestion();
}

void Teacher::checkIsQaQueueEmpty()
{
    if(qAqueue.empty())
        throw std::logic_error("empty questions container");
}

void Teacher::moveCurrentQuestionToAsked()
{
    lastAskedQuestion.setQA(qAqueue.front());
    qAqueue.pop();
}
