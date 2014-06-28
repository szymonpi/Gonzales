#pragma once

#include "../../GonzalesApp/qa/QAViewFactory.h"
#include "../gmock.h"

class QAViewFactoryMock: public QAViewFactory
{
public:
    MOCK_CONST_METHOD1(createQAView, std::shared_ptr<QAView>(const std::shared_ptr<QA> &qaData));
};
