
#include <memory>
#include "../gtest.h"
#include "../gmock.h"
#include "../../GonzalesApp/qa/QAsSelection/QARepeatPeriodChecker.h"
#include <utility>

using namespace testing;

class QARepeatPeriodCheckerTestSuite: public testing::Test
{

};

// NBA - DateSinceThereWasNoBadAnswer = NoBadAnswer

TEST_F(QARepeatPeriodCheckerTestSuite, noPeriodsGiven_ShouldThrow)
{
    std::set<Day> periods{};
    ASSERT_THROW(std::make_shared<QARepeatPeriodChecker>(periods), std::logic_error);
}

TEST_F(QARepeatPeriodCheckerTestSuite, onePeriodsGiven_noHistoryGiven_shouldReturnFalse)
{
    std::map<QDate, QA::AnswerRating> history;
    std::set<Day> periods{1};
    QARepeatPeriodChecker checker{periods};
    ASSERT_FALSE(checker.ShouldBeRepeated(history));
}

TEST_F(QARepeatPeriodCheckerTestSuite, onePeriodsGiven_oneNBAGiven_OneHistoryGivenWithCurrentDate_shouldReturnFalse)
{
    auto yesterday = QDate::currentDate().addDays(-1);
    std::map<QDate, QA::AnswerRating> history{std::make_pair(yesterday, QA::AnswerRating::Correct),
                std::make_pair(QDate::currentDate(), QA::AnswerRating::Correct)};
    std::set<Day> periods{1};
    QARepeatPeriodChecker checker{periods};
    ASSERT_FALSE(checker.ShouldBeRepeated(history));
}

TEST_F(QARepeatPeriodCheckerTestSuite, onePeriodsGiven_oneNBAGiven_shouldReturnTrue)
{
    auto yesterday = QDate::currentDate().addDays(-1);
    std::map<QDate, QA::AnswerRating> history{std::make_pair(yesterday, QA::AnswerRating::Correct)};
    std::set<Day> periods{1};
    QARepeatPeriodChecker checker{periods};
    ASSERT_TRUE(checker.ShouldBeRepeated(history));
}

TEST_F(QARepeatPeriodCheckerTestSuite, threePeriodsGiven_oneNBAGivenAndOneHistoryItem_shouldReturnTrue)
{
    auto fourDaysAgo = QDate::currentDate().addDays(-4);
    auto threeDaysAgo = QDate::currentDate().addDays(-3);
    std::map<QDate, QA::AnswerRating> history{std::make_pair(fourDaysAgo, QA::AnswerRating::Correct),
                                              std::make_pair(threeDaysAgo, QA::AnswerRating::Correct)};
    std::set<Day> periods{1, 2, 4};
    QARepeatPeriodChecker checker{periods};
    ASSERT_TRUE(checker.ShouldBeRepeated(history));
}

TEST_F(QARepeatPeriodCheckerTestSuite, threePeriodsGiven_oneNBAGivenAndThreeHistoryItem_shouldReturnFalse)
{
    auto fiveDaysAgo = QDate::currentDate().addDays(-5);
    auto fourDaysAgo = QDate::currentDate().addDays(-4);
    auto threeDaysAgo = QDate::currentDate().addDays(-3);
    auto oneDayAgo = QDate::currentDate().addDays(-1);
    std::map<QDate, QA::AnswerRating> history{std::make_pair(fiveDaysAgo, QA::AnswerRating::Correct),
                                              std::make_pair(fourDaysAgo, QA::AnswerRating::Correct),
                                              std::make_pair(threeDaysAgo, QA::AnswerRating::Correct),
                                              std::make_pair(oneDayAgo, QA::AnswerRating::Correct)};
    std::set<Day> periods{1, 2, 4};
    QARepeatPeriodChecker checker{periods};
    ASSERT_FALSE(checker.ShouldBeRepeated(history));
}

