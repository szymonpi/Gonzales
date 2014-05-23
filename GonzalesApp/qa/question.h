#pragma once
#include <string>
#include "../common/qtproxies/DataDeserializer.h"
#include "../common/qtproxies/DataSerializer.h"

class Question
{

public:
    Question(){}
    Question(std::string question)
    {
        this->question = question;
    }

    std::string getAsString() const
    {
        return question;
    }

    bool operator==(const Question &question) const
    {
        return !this->question.compare(question.getAsString());
    }

    void serialize(IDataSerializer &serializer) const
    {
        serializer.serialize(question.c_str());
    }

    void deserialize(IDataDeserializer&deserializer)
    {
        char *chars;

        deserializer.deserialize(chars);
        question = chars;
        delete chars;
    }

private:
    std::string question;
};
