#pragma once

#include "question.h"
#include "answer.h"
#include "stdexcept"
#include "../Common/FileException.h"

struct QA
{
    QA(Question question, Answer answer):
        question(question),
        answer(answer)
    {}

    QA(){}

    void serialize(IDataSerializer &serializer) const
    {
        question.serialize(serializer);
        answer.serialize(serializer);
    }

    void deserialize(IDataDeserializer&deserializer)
    {
        question.deserialize(deserializer);
        if(deserializer.status()==QDataStream::ReadPastEnd)
            throw FileException("empty file or can't read answer");
        answer.deserialize(deserializer);
    }

    bool operator ==(const QA &qA) const
    {
        return (qA.question == question) && (qA.answer == answer);
    }

    Question question;
    Answer answer;
};
