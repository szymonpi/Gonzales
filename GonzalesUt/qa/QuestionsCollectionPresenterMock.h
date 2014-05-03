#ifndef QUESTIONSCOLLECTIONPRESENTERMOCK_H
#define QUESTIONSCOLLECTIONPRESENTERMOCK_H
#include "../../GonzalesApp/IUIAdapters.h"
#include "../gmock.h"

class QuestionCollectionPresenteMock: public IQuestionCollectionPresenter
{
public:
    MOCK_METHOD1(presentQuestions, void(const std::vector<SimpleTree::Node<QA>> &));
};

#endif // QUESTIONSCOLLECTIONPRESENTERMOCK_H
