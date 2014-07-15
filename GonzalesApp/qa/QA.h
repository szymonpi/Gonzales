#pragma once

#include "Question.h"
#include "Answer.h"
#include "stdexcept"
#include "../common/FileException.h"
#include <QMultiMap>
#include <QDateTime>
#include <set>
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
        for(auto &kv: answersHistory)
        {
            serializer.serialize(unsigned(kv.second));
            QDate date = kv.first;
            serializer.serialize(date);
        }
        serializer.serialize(repetitionsHistory.size());
        for(auto &re: repetitionsHistory)
        {
            serializer.serialize(re);
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
            QDate date;
            deserializer.deserialize(date);
            answersHistory.emplace(date, QA::AnswerRating(value));
        }
        int repetitionSize = 0;
        deserializer.deserialize(repetitionSize);
        for(int i=0; i<repetitionSize; ++i)
        {
           QDate date;
           deserializer.deserialize(date);
           repetitionsHistory.insert(date);
        }
    }

    bool operator ==(const QA &qA) const
    {
        return (qA.question == question) && (qA.answer == answer);
    }

    void addHistoryEntry(const QDate &dateTime, AnswerRating questionResult)
    {
        answersHistory[dateTime] = questionResult;
    }

    std::map<QDate, AnswerRating> getAnswersHistory() const
    {
        return answersHistory;
    }


public:
    Question question;
    Answer answer;
    std::map<QDate, AnswerRating> answersHistory;
    std::set<QDate> repetitionsHistory;
};
