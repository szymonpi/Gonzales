#ifndef IANSWER_H
#define IANSWER_H

#include "../qa/Answer.h"

class IAnswerPresenter
{
public:
    virtual void presentAnswer(const Answer &question) = 0;
    virtual void clear() = 0;
    virtual ~IAnswerPresenter(){}
};

#endif // IANSWER_H
