#ifndef ANSWER_H
#define ANSWER_H
#include <string>

class Answer
{
public:
    Answer(std::string answer)
    {
        this->answer = answer;
    }

    std::string getAsString()
    {
        return answer;
    }

    bool operator==(const Answer &a2) const
    {
        return !answer.compare(a2.answer);
    }

private:
    std::string answer;

};

#endif // ANSWER_H
