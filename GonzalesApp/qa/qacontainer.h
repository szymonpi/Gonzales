#ifndef QACONTAINER_H
#define QACONTAINER_H

#include "question.h"
#include "answer.h"
#include "stdexcept"

struct QA
{
    QA(Question question, Answer answer):
        question(question),
        answer(answer)
    {}

    QA(){}

    bool operator ==(const QA &qA) const
    {
        return (qA.question == question) && (qA.answer == answer);
    }

    Question question;
    Answer answer;
};


struct QAContainer
{
    QAContainer():
        isAvailable(false),
        questionAnswer(Question("undefined"), Answer("Undefined"))
    {}

    void setQA(const QA &qA)
    {
        this->questionAnswer = qA;
        this->isAvailable = true;
    }

    QA qAObject() const
    {
        if(isAvailable)
            return questionAnswer;
        throw std::logic_error("empty asked questions");
    }

    void removeQuestion()
    {
        this->isAvailable = false;
        questionAnswer.answer = Answer("Undefined");
        questionAnswer.question = Question("Undefined");
    }

private:
    bool isAvailable = false;
    QA questionAnswer;
};

#endif // QACONTAINER_H
