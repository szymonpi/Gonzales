#pragma once

#include "QA.h"

class QAMarker;
class QuestionPresenter;
class AnswerPresenter;

class QAView
{
public:
    virtual void markAsKnown() = 0;
    virtual void markAsUnknown() = 0;
    virtual void presentQuestion() const = 0;
    virtual void presentAnswer() const = 0;
    ~QAView(){}
private:

};
