#pragma once
#include "../QA.h"
#include <set>
#include <deque>

typedef unsigned Day;

class QARepeatPeriodChecker
{
public:
    QARepeatPeriodChecker(std::set<Day> periods);
    bool ShouldBeRepeated(std::map<QDate, QA::AnswerRating> answerHistory);
    QDate getDateSinceThereWasNoBadAnswer(const std::map<QDate, QA::AnswerRating> &answerHistory) const;
    bool ShouldBeRepeated_deprecated(std::map<QDate, QA::AnswerRating> answerHistory);

    Day currentPeriod(std::deque<Day> &periodsToCheck);
    Day currentMaxPeriod(std::deque<Day> periodsToCheck, Day currentPeriod);
    QDate currentPeriodDate(const QDate& nBA, Day currentPer);
    QDate currentMaxPeriodDate(const QDate& nBA, Day currentMaxPer, QDate currentDay);
    bool isHistoryEntryInRange(QDate currentPerDate, QDate currentMaxPerDate, std::map<QDate, QA::AnswerRating> answerHistory);
private:
    std::set<Day> periods;
    QDate getPeriodDate(std::deque<Day> periodsToCheck);
    QDate getMaxPeriodDate(std::deque<Day> periodsToCheck);
};
