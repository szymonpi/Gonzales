#ifndef QUESTION_H
#define QUESTION_H
#include <string>

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

private:
    std::string question;
};

#endif // QUESTION_H
