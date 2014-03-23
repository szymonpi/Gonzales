#ifndef ANSWER_H
#define ANSWER_H
#include <string>
#include "../common/qtproxies/fileserializer.h"
#include "../common/qtproxies/filedeserializer.h"

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

    void serialize(CanSerializeData &serializer) const
    {
        serializer.serialize(answer.c_str());
    }

    void deserialize(CanDeserializeData &deserializer)
    {
        char *chars;

        deserializer.deserialize(chars);
        answer = chars;
        delete chars;
    }

private:
    std::string answer;

};

#endif // ANSWER_H
