#pragma once
#include "../Common/SimpleTree/Node.h"
#include "../qa/QA.h"

class Answer;
class Question;

class IQuestionCollectionPresenter
{
public:
    virtual void presentQuestions(const SimpleTree::Node<QA> &p_questions) = 0;
    virtual ~IQuestionCollectionPresenter(){}
};

