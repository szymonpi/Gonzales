#pragma once
#include "../../../QA.h"
#include <set>
#include <deque>
#include "IQARepeatPeriodChecker.h"

typedef unsigned Day;

class QARepeatPeriodChecker: public IQARepeatPeriodChecker
{
public:
    QARepeatPeriodChecker(std::set<Day> periods);
    bool shouldBeRepeated(const std::map<QDate, QA::AnswerRating>& answerHistory) const override;

private:
    std::set<Day> periods;
    std::set<QDate> getPeriodDates(QDate firstAnswerDate) const;
    bool containsRepeatPeriod(const QDate &firstAnswerDate, const QDate &lastAnswerDate) const;
    bool isPeriodInRange(QDate period, const QDate &leftBoundDate, const QDate &rightBoundDate) const;
};
