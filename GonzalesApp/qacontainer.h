#ifndef QACONTAINER_H
#define QACONTAINER_H

#include "question.h"
#include "answer.h"

struct QA
{
    QA(Question question, Answer answer):
        question(question),
        answer(answer)
    {}

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

    QA qAObject()
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
