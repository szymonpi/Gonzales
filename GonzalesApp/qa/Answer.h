#pragma once

#include <string>
#include "../common/qtproxies/DataSerializer.h"
#include "../common/qtproxies/DataDeserializer.h"

class Answer
{
public:
    Answer(){}
    Answer(const QString& answer)
    {
        this->answer = answer;
    }

    QString getAsString() const
    {
        return answer;
    }

    bool operator==(const Answer &a2) const
    {
        return !answer.compare(a2.answer);
    }

    void serialize(IDataSerializer &serializer) const
    {
        serializer.serialize(answer);
    }

    void deserialize(IDataDeserializer& deserializer)
    {
        QString str;
        deserializer.deserialize(str);
        answer = str;
    }

private:
    QString answer;

};
