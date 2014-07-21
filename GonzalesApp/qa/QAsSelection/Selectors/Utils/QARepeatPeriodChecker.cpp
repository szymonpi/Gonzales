#include "QARepeatPeriodChecker.h"
#include <deque>
#include <iterator>

QARepeatPeriodChecker::QARepeatPeriodChecker(std::set<Day> periods):
    periods(periods)
{
    if(periods.empty())
        throw std::logic_error("empty period list");
}

QDate QARepeatPeriodChecker::getDateSinceThereWasNoBadAnswer(const std::map<QDate, QA::AnswerRating> &answerHistory) const
{
    auto itemSinceThereWasntBadAnswer = answerHistory.rbegin();

    for(auto it = answerHistory.rbegin(); it != answerHistory.rend(); ++it)
    {
        if(it->second == QA::AnswerRating::Incorrect)
            break;
        itemSinceThereWasntBadAnswer = it;
    }

    return itemSinceThereWasntBadAnswer->first;
}

Day QARepeatPeriodChecker::currentPeriod(std::deque<Day> &periodsToCheck) const
{
    Day currentPeriod = periodsToCheck.front();
    periodsToCheck.pop_front();

    return currentPeriod;
}

Day QARepeatPeriodChecker::currentMaxPeriod(std::deque<Day> periodsToCheck, Day currentPeriod) const
{
    Day currentMaxPeriod;
    if(periodsToCheck.empty())
        currentMaxPeriod = currentPeriod*2;
    else
        currentMaxPeriod = periodsToCheck.front();

    return currentMaxPeriod;
}

QDate QARepeatPeriodChecker::currentPeriodDate(const QDate &nBA, Day currentPer) const
{
    auto currentPeriodDate = nBA.addDays(currentPer);

    return currentPeriodDate;
}

QDate QARepeatPeriodChecker::currentMaxPeriodDate(const QDate &nBA, Day currentMaxPer, QDate currentDay) const
{
    auto currentMaxPeriodDate = nBA.addDays(currentMaxPer);
    currentMaxPeriodDate =  currentMaxPeriodDate > currentDay ?
                            QDate::currentDate() : currentMaxPeriodDate;

    return currentMaxPeriodDate;
}

bool QARepeatPeriodChecker::isHistoryEntryInRange(QDate currentPerDate,
                                                  QDate currentMaxPerDate,
                                                  std::map<QDate, QA::AnswerRating> answerHistory) const
{
    auto lowerBoundHistory = answerHistory.lower_bound(currentPerDate);
    if(lowerBoundHistory == answerHistory.end())
        return false;
    if(lowerBoundHistory->first > currentMaxPerDate)
        return false;
    return true;
}

bool QARepeatPeriodChecker::shouldBeRepeated(const std::map<QDate, QA::AnswerRating> &answerHistory) const
{
    if(answerHistory.empty())
        return false;
    auto currentDay = QDate::currentDate();
    auto nBA = getDateSinceThereWasNoBadAnswer(answerHistory);

    std::deque<Day> periodsToCheck(periods.begin(), periods.end());

    while(!periodsToCheck.empty())
    {
        Day currentPer = currentPeriod(periodsToCheck);
        Day currentMaxPer = currentMaxPeriod(periodsToCheck, currentPer);

        QDate currentPerDate = currentPeriodDate(nBA, currentPer);
        QDate currentMaxPerDate = currentMaxPeriodDate(nBA, currentMaxPer, currentDay);
        if(!isHistoryEntryInRange(currentPerDate, currentMaxPerDate, answerHistory))
            return true;
    }

    return false;
}
