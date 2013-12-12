#ifndef QUESTION_H
#define QUESTION_H

class Question
{

public:
    Question(std::string question)
    {
        this->question = question;
    }

    std::string getString() const
    {
        return question;
    }

private:
    std::string question;
};

#endif // QUESTION_H
