#ifndef IQUESTIONCOLLECTIONPRESENTER_H
#define IQUESTIONCOLLECTIONPRESENTER_H

#include "../Common/SimpleTree/Node.h"
#include "../qa/QAContainer.h"

class Answer;
class Question;

class IQuestionCollectionPresenter
{
public:
    virtual void presentQuestions(const SimpleTree::Node<QA> &p_questions) = 0;
    virtual ~IQuestionCollectionPresenter(){}
};

#endif // IQUESTIONCOLLECTIONPRESENTER_H
