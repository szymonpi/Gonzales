#pragma once

#include <vector>
#include "../qa/qacontainer.h"

class ITeacher
{
public:
    virtual void setQuestions(const std::vector<QA> &questions) = 0;
    virtual void showCorrectAnswer(const QString &question) const = 0;
    virtual int questionsToLearnNum() const = 0;
    virtual void showNextQuestion() = 0;
};

