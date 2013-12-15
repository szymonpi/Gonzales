#ifndef QUESTION_H
#define QUESTION_H


class Question
{

public:
    Question(std::string question)
    {
        this->question = question;
    }

    std::string geAstString() const
    {
        return question;
    }

    bool operator==(const Question &question) const
    {
        return !this->question.compare(question.geAstString());
    }

private:
    std::string question;
};

#endif // QUESTION_H
