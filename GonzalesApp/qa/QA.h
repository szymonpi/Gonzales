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
            QDateTime date = kv.first;
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
            QDateTime dateTime;
            deserializer.deserialize(dateTime);
            answersHistory.emplace(dateTime, QA::AnswerRating(value));
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

    std::map<QDateTime, AnswerRating> getAnswersHistory()
    {
        return answersHistory;
    }

    bool wasWrongAnswered()
    {
        return answersHistory.end() != std::find_if(answersHistory.begin(), answersHistory.end(),
                            [](const std::pair<QDateTime, AnswerRating> &answer) -> bool
                              { return answer.second == AnswerRating::Incorrect; });
    }

private:
    Question question;
    Answer answer;
    std::map<QDateTime, AnswerRating> answersHistory;
};
