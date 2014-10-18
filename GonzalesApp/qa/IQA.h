#pragma once

class IDataSerializer;
class IDataDeserializer;
class IQAPresenter;
class QString;

class IQA
{
public:
    virtual void serialize(IDataSerializer &serializer) const = 0;
    virtual void deserialize(IDataDeserializer& deserializer) = 0;

    virtual bool isLearned() const = 0;
    virtual bool hasHistory() const = 0;

    virtual void markAsKnown(const QDate& date) = 0;
    virtual void markAsUnknown(const QDate& date) = 0;

    virtual void presentQuestion(IQAPresenter& presenter) = 0;
    virtual void presentAnswer(IQAPresenter& presenter) = 0;

    virtual QString getQuestionStringRepresentation() = 0;
    virtual QString getAnswerStringRepresentation() = 0;

    virtual bool operator ==(const IQA &qA) const = 0;

    virtual ~IQA(){}
};
