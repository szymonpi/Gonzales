#ifndef QUESTIONSCOLLECTIONPRESENTERMOCK_H
#define QUESTIONSCOLLECTIONPRESENTERMOCK_H
#include "../../GonzalesApp/uiobservers/IUIAdapters.h"
#include "../gmock.h"

class QuestionCollectionPresenteMock: public IQuestionCollectionPresenter
{
public:
    MOCK_METHOD1(presentQuestions, void(const SimpleTree::Node<QA> &));
};

#endif // QUESTIONSCOLLECTIONPRESENTERMOCK_H
