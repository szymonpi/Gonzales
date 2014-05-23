#pragma once

#include <string>
#include "../common/qtproxies/DataSerializer.h"
#include "../common/qtproxies/DataDeserializer.h"

class Answer
{
public:
    Answer(){}
    Answer(std::string answer)
    {
        this->answer = answer;
    }

    std::string getAsString() const
    {
        return answer;
    }

    bool operator==(const Answer &a2) const
    {
        return !answer.compare(a2.answer);
    }

    void serialize(IDataSerializer &serializer) const
    {
        serializer.serialize(answer.c_str());
    }

    void deserialize(IDataDeserializer&deserializer)
    {
        char *chars;

        deserializer.deserialize(chars);
        answer = chars;
        delete chars;
    }

private:
    std::string answer;

};
