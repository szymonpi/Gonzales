#ifndef QUESTION_H
#define QUESTION_H
#include <string>
#include "../common/qtproxies/filedeserializer.h"
#include "../common/qtproxies/fileserializer.h"

class Question
{

public:
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

    void serialize(CanSerializeData &serializer)
    {
        serializer.serialize(question.c_str());
    }

    void deserialize(CanDeserializeData &deserializer)
    {
        char *chars;

        deserializer.deserialize(chars);
        question = chars;
        delete chars;
    }

private:
    std::string question;
};

#endif // QUESTION_H
