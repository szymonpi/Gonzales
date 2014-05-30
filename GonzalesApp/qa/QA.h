#pragma once

#include "question.h"
#include "answer.h"
#include "stdexcept"
#include "../Common/FileException.h"
#include <QMultiMap>
#include <QDateTime>

class QA
{
public:
    enum class AnswerRating
    {
        Correct,
        Incorrect
    };

    QA(Question question, Answer answer):
        question(question),
        answer(answer)
    {}

    QA(){}

    void serialize(IDataSerializer &serializer) const
    {
        question.serialize(serializer);
        answer.serialize(serializer);
        serializer.serialize(answersHistory.size());
        for(auto it = answersHistory.begin(); it != answersHistory.end(); ++it)
        {
            serializer.serialize(unsigned(it.value()));
            QDateTime date = it.key();
            serializer.serialize(date.date().day());
            serializer.serialize(date.date().month());
            serializer.serialize(date.date().year());
            serializer.serialize(date.time().hour());
            serializer.serialize(date.time().minute());
        }
    }

    void deserialize(IDataDeserializer& deserializer)
    {
        question.deserialize(deserializer);
        answer.deserialize(deserializer);
        int historySize = 0;
        deserializer.deserialize(historySize);
        for(int i = 0; i<historySize; ++i)
        {
            unsigned value = 0;
            deserializer.deserialize(value);
            int day = 0;
            int month = 0;
            int year = 0;
            int hour = 0;
            int minute = 0;
            deserializer.deserialize(day);
            deserializer.deserialize(month);
            deserializer.deserialize(year);
            deserializer.deserialize(hour);
            deserializer.deserialize(minute);
            QDateTime date(QDate(year, month, day));
            answersHistory.insert(date, QA::AnswerRating(value));
        }
    }

    bool operator ==(const QA &qA) const
    {
        return (qA.question == question) && (qA.answer == answer);
    }

    Question getQuestion()
    {
        return question;
    }

    Answer getAnswer()
    {
        return answer;
    }

    void addHistoryEntry(const QDateTime &dateTime, AnswerRating questionResult)
    {
        answersHistory[dateTime] = questionResult;
    }

    QMultiMap<QDateTime, AnswerRating> getAnswersHistory()
    {
        return answersHistory;
    }

private:
    Question question;
    Answer answer;
    QMap<QDateTime, AnswerRating> answersHistory;
};
