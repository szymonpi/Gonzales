#include "teacher.h"
#include <algorithm>

Teacher::Teacher():
    qAToLearn(),
    lastAskedQuestion()
{}


Teacher::Teacher(const Teacher::QAQueue &questions):
    qAToLearn(questions),
    allQA(questions),
    lastAskedQuestion()
{}

void Teacher::setQuestions(const Teacher::QAQueue &questions)
{
    this->allQA = questions;
    this->qAToLearn = questions;
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

Answer Teacher::getCorrectAnswer(const Question &question) const
{
    QAQueue::const_iterator it = std::find_if(allQA.begin(),
                                              allQA.end(),
                                              [&question] (const QAPair &qa) { return qa.question == question; });
    if(it==allQA.end())
        throw std::logic_error("Can't faind question:");
    return (*it).answer;
}

int Teacher::questionsToLearnNum() const
{
    return qAToLearn.size();
}

Teacher::QAQueue Teacher::getQAs() const
{
    return allQA;
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
