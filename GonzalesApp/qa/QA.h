#pragma once

#include <set>
#include <memory>

#include <QDateTime>

#include "Question.h"
#include "Answer.h"
#include "../common/FileException.h"
#include "IQA.h"

class QA : public IQA
{
public:
    enum class AnswerRating
    {
        Correct = 99,
        Incorrect = 100
    };

    QA(QString question, QString answer);
    QA();

    void serialize(IDataSerializer &serializer) const;
    void deserialize(IDataDeserializer& deserializer);

    bool operator ==(const IQA &qA) const;
    bool isLearned() const;

    void markAsKnown(const QDate& date);
    void markAsUnknown(const QDate& date);

    void presentAnswer();
    void presentQuestion();

public:
    QString question;
    QString answer;
    std::map<QDate, AnswerRating> answersHistory;
    std::set<QDate> repetitionsHistory;
};
