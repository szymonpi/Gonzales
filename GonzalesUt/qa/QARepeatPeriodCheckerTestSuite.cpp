
#include <memory>
#include "../gtest.h"
#include "../gmock.h"
#include "../../GonzalesApp/qa/QAsSelection/Selectors/Utils/QARepeatPeriodChecker.h"
#include <utility>

using namespace testing;

class IsForRepeatQATestSuite: public testing::Test
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
TEST_F(IsForRepeatQATestSuite, noPeriodsGiven_ShouldThrow)
{
    std::set<Day> periods{};

    ASSERT_THROW(IsForRepeatQA{periods}, std::logic_error);
}

//0.b
TEST_F(IsForRepeatQATestSuite, onePeriodGiven_IncorrectLastAnswerGiven_ShouldReturnFalse)
{
    IsForRepeatQA checker{onePeriod};
    std::shared_ptr<QA> qa = std::make_shared<QA>();
    qa->markAsUnknown(currentDay);
    ASSERT_FALSE(checker(qa));
}
//1
TEST_F(IsForRepeatQATestSuite,
       OnePeriodGiven_AnswerHistoryWithTodayGivenShouldReturnFalse)
{
    IsForRepeatQA checker{onePeriod};

    std::shared_ptr<QA> qa = std::make_shared<QA>();
    qa->markAsKnown(currentDay);
    ASSERT_FALSE(checker(qa));
}

//2
TEST_F(IsForRepeatQATestSuite, OnePeriodGiven_AnswerHistoryWithYesterdayGivenShouldReturnTrue)
{
    IsForRepeatQA checker{onePeriod};
    std::shared_ptr<QA> qa = std::make_shared<QA>();
    qa->markAsKnown(yesterday);

    ASSERT_TRUE(checker(qa));
}
//3
TEST_F(IsForRepeatQATestSuite,
       OnePeriodGiven_AnswerHistoryWithDayBeforeYesterdayGivenShouldReturnTrue)
{
    IsForRepeatQA checker{onePeriod};
    std::shared_ptr<QA> qa = std::make_shared<QA>();
    qa->markAsKnown(dayBeforeYesterday);

    ASSERT_TRUE(checker(qa));
}
//4
TEST_F(IsForRepeatQATestSuite,
       OnePeriodGiven_AnswerHistoryWithdayBeforeYesterdayAndYesterdayGivenShouldReturnFalse)
{
    IsForRepeatQA checker{onePeriod};
    std::shared_ptr<QA> qa = std::make_shared<QA>();
    qa->markAsKnown(yesterday);
    qa->markAsKnown(dayBeforeYesterday);
    ASSERT_FALSE(checker(qa));
}
//5
TEST_F(IsForRepeatQATestSuite,
       OnePeriodGiven_AnswerHistoryWithYesterdayAndTodayGivenShouldReturnFalse)
{
    IsForRepeatQA checker{onePeriod};
    std::shared_ptr<QA> qa = std::make_shared<QA>();
    qa->markAsKnown(yesterday);
    qa->markAsKnown(currentDay);
    ASSERT_FALSE(checker(qa));
}
//6
TEST_F(IsForRepeatQATestSuite,
       TwoPeriodGiven_AnswerHistoryWithYesterdayAndDayBeforeYesterdayGivenShouldReturnTrue)
{
    IsForRepeatQA checker{twoPeriods};
    std::shared_ptr<QA> qa = std::make_shared<QA>();
    qa->markAsKnown(dayBeforeYesterday);
    qa->markAsKnown(yesterday);
    ASSERT_TRUE(checker(qa));
}

//7
TEST_F(IsForRepeatQATestSuite,
       TwoPeriodGiven_AnswerHistoryWithTodayYesterdayAndDayBeforeYesterdayGivenShouldReturn_False)
{
    IsForRepeatQA checker{twoPeriods};
    std::shared_ptr<QA> qa = std::make_shared<QA>();
    qa->markAsKnown(currentDay);
    qa->markAsKnown(dayBeforeYesterday);
    qa->markAsKnown(yesterday);

    ASSERT_FALSE(checker(qa));
}

//8
TEST_F(IsForRepeatQATestSuite,
       TwoPeriodGiven_AnswerHistoryWithTodayYesterdayAndDayBeforeYesterdayGivenShouldReturnTrue)
{
    IsForRepeatQA checker{threePeriods};
    std::shared_ptr<QA> qa = std::make_shared<QA>();
    qa->markAsKnown(dayBeforeYesterday);
    qa->markAsKnown(threeDaysAgo);
    qa->markAsKnown(fourDaysAgo);

    ASSERT_TRUE(checker(qa));
}

//9
TEST_F(IsForRepeatQATestSuite,
       TwoPeriodGiven_AnswerHistoryWithThreeDaysAgoShouldReturnTrue)
{
    IsForRepeatQA checker{{5}};
    std::shared_ptr<QA> qa = std::make_shared<QA>();
    qa->markAsKnown(threeDaysAgo);

    ASSERT_FALSE(checker(qa));
}

//10
TEST_F(IsForRepeatQATestSuite,
       ThreePeriodGiven_AnswerHistoryWithThreeDaysAgoShouldReturnTrue)
{
    IsForRepeatQA checker{fourPeriods};
    std::shared_ptr<QA> qa = std::make_shared<QA>();
    qa->markAsKnown(fiveDaysAgo);
    qa->markAsKnown(fourDaysAgo);
    qa->markAsKnown(threeDaysAgo);
    qa->markAsKnown(dayBeforeYesterday);
    qa->markAsKnown(yesterday);
    qa->markAsKnown(currentDay);

    ASSERT_FALSE(checker(qa));
}


