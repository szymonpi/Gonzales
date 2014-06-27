#pragma once

#include "Question.h"
#include "Answer.h"
#include "stdexcept"
#include "../common/FileException.h"
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
        for(auto &kv: answersHistory)
        {
            serializer.serialize(unsigned(kv.second));
            QDate date = kv.first;
            serializer.serialize(date);
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

    bool wasWrongAnswered() const
    {
        return answersHistory.end() != std::find_if(answersHistory.begin(), answersHistory.end(),
                            [](const std::pair<QDate, AnswerRating> &answer) -> bool
                              { return answer.second == AnswerRating::Incorrect; });
    }

    bool wasLastWrongAnswered() const
    {
        return (--answersHistory.end())->second == QA::AnswerRating::Incorrect;
    }

    size_t answerHistorySize() const
    {
        return answersHistory.size();
    }

public:
    Question question;
    Answer answer;
    std::map<QDate, AnswerRating> answersHistory;
};
