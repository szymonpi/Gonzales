#include "QA.h"
#include "../common/qtproxies/IDataDeserializer.h"
#include "../common/qtproxies/IDataSerializer.h"

QA::QA(QString question, QString answer):
    question(question),
    answer(answer)
{}

QA::QA(){}

void QA::serialize(IDataSerializer &serializer) const
{
    serializer.serialize(question);
    serializer.serialize(answer);

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

void QA::deserialize(IDataDeserializer &deserializer)
{
    deserializer.deserialize(question);
    deserializer.deserialize(answer);

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

bool QA::operator ==(const IQA &qA) const
{
    const QA* qa_ = static_cast<const QA*>(&qA);
    if(!qa_)
        return false;

    return qa_->question == question &&
            qa_->answer == answer &&
            qa_->answersHistory == answersHistory;
}

bool QA::isLearned() const
{
    if(answersHistory.empty())
        return false;
    auto lastItem = --answersHistory.end();
    if(lastItem->second == QA::AnswerRating::Incorrect)
        return false;
    return true;
}

bool QA::hasHistory() const
{
    return !answersHistory.empty();
}

void QA::markAsKnown(const QDate &date)
{
    QA::AnswerRating answerRating = QA::AnswerRating::Correct;
    if(answersHistory.find(date) != answersHistory.end())
        if(answersHistory[date] == QA::AnswerRating::Incorrect)
            answerRating = QA::AnswerRating::Incorrect;

    answersHistory[date] = answerRating;
}

void QA::markAsUnknown(const QDate &date)
{
    answersHistory[date] =  QA::AnswerRating::Incorrect;
}

void QA::presentAnswer()
{

}

void QA::presentQuestion()
{

}
