#include "QARepeatPeriodChecker.h"
#include "../../../../common/Algorithms.h"
#include <deque>
#include <iterator>
#include <functional>

QARepeatPeriodChecker::QARepeatPeriodChecker(std::set<Day> periods):
    periods(periods)
{
    if(periods.empty())
        throw std::logic_error("empty period list");
}

QDate function(const std::pair<QDate,QA::AnswerRating>& answer)
{
    return answer.first;
}

bool QARepeatPeriodChecker::shouldBeRepeated(
        const std::map<QDate, QA::AnswerRating>& answerHistory) const
{
    if(answerHistory.empty())
        return false;
    if((--answerHistory.end())->second == QA::AnswerRating::Incorrect)
        return false;

    return containsRepeatPeriod(answerHistory.begin()->first,
                                (--answerHistory.end())->first);
}

bool QARepeatPeriodChecker::containsRepeatPeriod(const QDate& firstAnswerDate,
                                                 const QDate& lastAnswerDate) const
{
    const std::set<QDate> periodDates = getPeriodDates(firstAnswerDate);
    for(const auto& period: periodDates)
        if(isPeriodInRange(period, lastAnswerDate, QDate::currentDate()))
            return true;
    return false;
}

std::set<QDate> QARepeatPeriodChecker::getPeriodDates(QDate firstAnswerDate) const
{
    std::set<QDate> periodDays;
    for(const auto& period: periods)
        periodDays.insert(firstAnswerDate.addDays(period));

    return periodDays;
}

bool QARepeatPeriodChecker::isPeriodInRange(QDate period,
                                            const QDate& leftBoundDate,
                                            const QDate& rightBoundDate) const
{
    return period > leftBoundDate && period <= rightBoundDate;
}
