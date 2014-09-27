
#include <memory>
#include "../gtest.h"
#include "../gmock.h"
#include "../../GonzalesApp/qa/QAsSelection/Selectors/Utils/QARepeatPeriodChecker.h"
#include <utility>

using namespace testing;

class QARepeatPeriodCheckerTestSuite: public testing::Test
{
public:
    std::set<Day> onePeriod{1};
    std::set<Day> twoPeriods{1, 2};
    std::set<Day> threePeriods{1, 2, 3};
    std::set<Day> fourPeriods{1, 2, 3, 4};
    QDate currentDay = QDate::currentDate();
    QDate yesterday = currentDay.addDays(-1);
    QDate dayBeforeYesterday = currentDay.addDays(-2);
    QDate threeDaysAgo = currentDay.addDays(-3);
    QDate fourDaysAgo = currentDay.addDays(-4);
    QDate fiveDaysAgo = currentDay.addDays(-5);

};

//0.a
TEST_F(QARepeatPeriodCheckerTestSuite, noPeriodsGiven_ShouldThrow)
{
    std::set<Day> periods{};

    ASSERT_THROW(std::make_shared<QARepeatPeriodChecker>(periods), std::logic_error);
}

//0.b
TEST_F(QARepeatPeriodCheckerTestSuite, onePeriodGiven_IncorrectLastAnswerGiven_ShouldReturnFalse)
{
    QARepeatPeriodChecker checker{onePeriod};
    ASSERT_FALSE(checker.shouldBeRepeated({{currentDay, QA::AnswerRating::Incorrect}}));
}
//1
TEST_F(QARepeatPeriodCheckerTestSuite,
       OnePeriodGiven_AnswerHistoryWithTodayGivenShouldReturnFalse)
{
    QARepeatPeriodChecker checker{onePeriod};
    ASSERT_FALSE(checker.shouldBeRepeated({{currentDay, QA::AnswerRating::Correct}}));
}

//1
TEST_F(QARepeatPeriodCheckerTestSuite,
       OnePeriodGiven_emptyAnswerHistoryGivenShouldReturnFalse)
{
    QARepeatPeriodChecker checker{onePeriod};
    ASSERT_FALSE(checker.shouldBeRepeated({}));
}
//2
TEST_F(QARepeatPeriodCheckerTestSuite, OnePeriodGiven_AnswerHistoryWithYesterdayGivenShouldReturnTrue)
{
    QARepeatPeriodChecker checker{onePeriod};
    ASSERT_TRUE(checker.shouldBeRepeated({{yesterday, QA::AnswerRating::Correct}}));
}
//3
TEST_F(QARepeatPeriodCheckerTestSuite,
       OnePeriodGiven_AnswerHistoryWithDayBeforeYesterdayGivenShouldReturnTrue)
{
    QARepeatPeriodChecker checker{onePeriod};
    ASSERT_TRUE(checker.shouldBeRepeated({{dayBeforeYesterday, QA::AnswerRating::Correct}}));
}
//4
TEST_F(QARepeatPeriodCheckerTestSuite,
       OnePeriodGiven_AnswerHistoryWithdayBeforeYesterdayAndYesterdayGivenShouldReturnFalse)
{
    QARepeatPeriodChecker checker{onePeriod};
    ASSERT_FALSE(checker.shouldBeRepeated({{yesterday, QA::AnswerRating::Correct},
                                          {dayBeforeYesterday, QA::AnswerRating::Correct}}));
}
//5
TEST_F(QARepeatPeriodCheckerTestSuite,
       OnePeriodGiven_AnswerHistoryWithYesterdayAndTodayGivenShouldReturnFalse)
{
    QARepeatPeriodChecker checker{onePeriod};
    ASSERT_FALSE(checker.shouldBeRepeated({{yesterday, QA::AnswerRating::Correct},
                                          {currentDay, QA::AnswerRating::Correct}}));
}
//6
TEST_F(QARepeatPeriodCheckerTestSuite,
       TwoPeriodGiven_AnswerHistoryWithYesterdayAndDayBeforeYesterdayGivenShouldReturnTrue)
{
    QARepeatPeriodChecker checker{twoPeriods};
    ASSERT_TRUE(checker.shouldBeRepeated({{dayBeforeYesterday, QA::AnswerRating::Correct},
                                          {yesterday, QA::AnswerRating::Correct}}));
}

//7
TEST_F(QARepeatPeriodCheckerTestSuite,
       TwoPeriodGiven_AnswerHistoryWithTodayYesterdayAndDayBeforeYesterdayGivenShouldReturn_False)
{
    QARepeatPeriodChecker checker{twoPeriods};

    ASSERT_FALSE(checker.shouldBeRepeated({{currentDay, QA::AnswerRating::Correct},
                                          {dayBeforeYesterday, QA::AnswerRating::Correct},
                                          {yesterday, QA::AnswerRating::Correct}}));
}

//8
TEST_F(QARepeatPeriodCheckerTestSuite,
       TwoPeriodGiven_AnswerHistoryWithTodayYesterdayAndDayBeforeYesterdayGivenShouldReturnTrue)
{
    QARepeatPeriodChecker checker{threePeriods};

    ASSERT_TRUE(checker.shouldBeRepeated({{dayBeforeYesterday, QA::AnswerRating::Correct},
                                          {threeDaysAgo, QA::AnswerRating::Correct},
                                          {fourDaysAgo, QA::AnswerRating::Correct}}));
}

//9
TEST_F(QARepeatPeriodCheckerTestSuite,
       TwoPeriodGiven_AnswerHistoryWithThreeDaysAgoShouldReturnTrue)
{
    QARepeatPeriodChecker checker{{5}};

    ASSERT_FALSE(checker.shouldBeRepeated({{threeDaysAgo, QA::AnswerRating::Correct}}));
}

//10
TEST_F(QARepeatPeriodCheckerTestSuite,
       ThreePeriodGiven_AnswerHistoryWithThreeDaysAgoShouldReturnTrue)
{
    QARepeatPeriodChecker checker{fourPeriods};

    ASSERT_FALSE(checker.shouldBeRepeated({{fiveDaysAgo, QA::AnswerRating::Correct},
                                           {fourDaysAgo, QA::AnswerRating::Correct},
                                           {threeDaysAgo, QA::AnswerRating::Correct},
                                           {dayBeforeYesterday, QA::AnswerRating::Correct},
                                           {yesterday, QA::AnswerRating::Correct},
                                           {currentDay, QA::AnswerRating::Correct}}));
}


