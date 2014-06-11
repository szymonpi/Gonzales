#pragma once
#include <string>
#include "../common/qtproxies/DataDeserializer.h"
#include "../common/qtproxies/DataSerializer.h"

class Question
{

public:
    Question(){}
    Question(const QString &question)
    {
        this->question = question;
    }

    QString getAsString() const
    {
        return question;
    }

    bool operator==(const Question &question) const
    {
        return !this->question.compare(question.getAsString());
    }

    void serialize(IDataSerializer &serializer) const
    {
        serializer.serialize(question);
    }

    void deserialize(IDataDeserializer&deserializer)
    {
        QString str;
        deserializer.deserialize(str);
        question = str;
    }

private:
    QString question;
};
