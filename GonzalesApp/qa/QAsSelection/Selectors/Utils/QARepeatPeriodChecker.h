#pragma once
#include "../../../QA.h"
#include <set>
#include <deque>
#include "IQARepeatPeriodChecker.h"

typedef unsigned Day;

class IsForRepeatQA
{
public:
    IsForRepeatQA(std::set<Day> periods);

    bool operator()(std::shared_ptr<QA> qa) const
    {
        return shouldBeRepeated(qa->answersHistory);
    }

private:
    bool shouldBeRepeated(const std::map<QDate, QA::AnswerRating>& answerHistory) const;
    std::set<Day> periods;
    std::set<QDate> getPeriodDates(QDate firstAnswerDate) const;
    bool containsRepeatPeriod(const QDate &firstAnswerDate, const QDate &lastAnswerDate) const;
    bool isPeriodInRange(QDate period, const QDate &leftBoundDate, const QDate &rightBoundDate) const;
};
