#ifndef PRESENTERSMOCK_H
#define PRESENTERSMOCK_H

#include "../gmock.h"
#include "../../GonzalesApp/IUIAdapters.h"


class QuestionPresenterMock: public IQuestionPresenter
{
public:
    MOCK_METHOD1(presentQuestion, void(const Question &));
    MOCK_METHOD0(clear, void());
};

class AnswerPresenterMock: public IAnswerPresenter
{
public:
    MOCK_METHOD1(presentAnswer, void(const Answer &));
    MOCK_METHOD0(clear, void());
};

#endif // PRESENTERSMOCK_H
