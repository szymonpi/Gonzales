#pragma once

#include "../../GonzalesApp/qa/QAsSelection/Selectors/Utils/IQARepeatPeriodChecker.h"
#include "../gmock.h"

class QARepeatPeriodCheckerMock: public IQARepeatPeriodChecker
{
public:
    MOCK_CONST_METHOD1(shouldBeRepeated, bool(const std::map<QDate, QA::AnswerRating> &answerHistory));
};

