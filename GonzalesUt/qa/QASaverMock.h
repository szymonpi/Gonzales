#pragma once

#include "../../GonzalesApp/qa/QASaver.h"
#include "../gmock.h"

class QASaverMock: public IQASaver
{
public:
    MOCK_METHOD1(save, void(const SimpleTree::Node<QA> &QuestionAnswers));
};

