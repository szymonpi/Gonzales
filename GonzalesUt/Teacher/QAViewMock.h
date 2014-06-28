#pragma once
#include "../../GonzalesApp/qa/QAView.h"

#include "../gmock.h"


class QAViewMock: public QAView
{
public:
    MOCK_METHOD0(markAsKnown, void());
    MOCK_METHOD0(markAsUnknown, void());
    MOCK_CONST_METHOD0(presentQuestion, void());
    MOCK_CONST_METHOD0(presentAnswer, void());
};
