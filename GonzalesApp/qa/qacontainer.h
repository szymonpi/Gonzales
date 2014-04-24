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

    void serialize(CanSerializeData &serializer) const
    {
        question.serialize(serializer);
        answer.serialize(serializer);
        serializer.serialize(m_toLearn);
    }

    void deserialize(CanDeserializeData &deserializer)
    {
        question.deserialize(deserializer);
        answer.deserialize(deserializer);
        deserializer.deserialize(m_toLearn);
    }

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
