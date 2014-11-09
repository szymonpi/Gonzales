#pragma once
#include "../../../QA.h"
#include <set>
#include <deque>

class IQARepeatPeriodChecker
{
public:
    virtual bool shouldBeRepeated(const std::map<QDate, QA::AnswerRating> &answerHistory) const = 0;
    virtual ~IQARepeatPeriodChecker(){}
};
