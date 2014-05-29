#pragma once

#include "question.h"
#include "answer.h"
#include "stdexcept"
#include "../Common/FileException.h"
#include <QMap>
#include <QDate>

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
        serializer.serialize(answeredHistory.size());
        for(auto it = answeredHistory.begin(); it != answeredHistory.end(); ++it)
        {
            serializer.serialize(it.value());
            QDate date = it.key();
            serializer.serialize(date.day());
            serializer.serialize(date.month());
            serializer.serialize(date.year());
        }
    }

    void deserialize(IDataDeserializer& deserializer)
    {
        question.deserialize(deserializer);
        if(deserializer.status()==QDataStream::ReadPastEnd)
            throw FileException("empty file or can't read answer");
        answer.deserialize(deserializer);
        int historySize = 0;
        deserializer.deserialize(historySize);
        for(int i = 0; i<historySize; ++i)
        {
            bool value = 0;
            deserializer.deserialize(value);
            int day = 0;
            int month = 0;
            int year = 0;
            deserializer.deserialize(day);
            deserializer.deserialize(month);
            deserializer.deserialize(year);
            QDate date(year, month, day);
            answeredHistory.insert(date, value);
        }
    }

    bool operator ==(const QA &qA) const
    {
        return (qA.question == question) && (qA.answer == answer);
    }

    Question question;
    Answer answer;
    QMap<QDate, bool> answeredHistory;
};
