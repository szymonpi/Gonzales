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

    bool toLearn() const
    {
        return m_toLearn;
    }

    Question question;
    Answer answer;
    bool m_toLearn;
};

#endif // QACONTAINER_H
