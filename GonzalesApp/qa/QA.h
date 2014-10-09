#pragma once

#include <set>
#include <memory>

#include <QDateTime>

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
    bool hasHistory() const;

    void markAsKnown(const QDate& date);
    void markAsUnknown(const QDate& date);

    void presentAnswer();
    void presentQuestion();

public: //change to private
    QString question;
    QString answer;
    std::map<QDate, AnswerRating> answersHistory;
    std::set<QDate> repetitionsHistory;
};
