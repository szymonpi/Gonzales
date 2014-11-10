#pragma once

#include <set>
#include <memory>
#include <map>
#include <QDateTime>

#include "../common/FileException.h"
#include "IQA.h"
#include "../uiobservers/IQAPresenter.h"

class QA : public IQA
{
public:
    friend class IsForRepeatQA;
    enum class AnswerRating
    {
        Correct = 99,
        Incorrect = 100
    };

    QA(QString question, QString answer);
    QA();

    void serialize(IDataSerializer &serializer) const;
    void deserialize(IDataDeserializer& deserializer);

    bool isLearned() const;
    bool hasHistory() const;

    void markAsKnown(const QDate& date);
    void markAsUnknown(const QDate& date);

    QString getQuestionStringRepresentation();
    QString getAnswerStringRepresentation();

    void presentAnswer(IQAPresenter& presenter); /// @todo move to constructor?
    void presentQuestion(IQAPresenter& presenter); /// @todo move to constructor?

private:
    QString question;
    QString answer;
    std::map<QDate, AnswerRating> answersHistory;
};
