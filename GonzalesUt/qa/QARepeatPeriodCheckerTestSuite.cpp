
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

//TEST_F(QARepeatPeriodCheckerTestSuite, onePeriodsGiven_oneHistoryGivenWithYesterday_shouldReturnTRUE)
//{
//    auto yesterday = QDate::currentDate().addDays(-1);
//    std::map<QDate, QA::AnswerRating> history{std::make_pair(yesterday, QA::AnswerRating::Correct)};
//    std::set<Day> periods{1};
//    QARepeatPeriodChecker checker{periods};
//    ASSERT_TRUE(checker.ShouldBeRepeated(history));
//}

//TEST_F(QARepeatPeriodCheckerTestSuite, TwoPeriodsGiven_TwoHistoryGiven_shouldReturnTRUE)
//{
//    auto threeDaysAgo = QDate::currentDate().addDays(-3);
//    auto fourDaysAgo = QDate::currentDate().addDays(-4);
//    std::map<QDate, QA::AnswerRating> history{std::make_pair(threeDaysAgo, QA::AnswerRating::Correct),
//                                              std::make_pair(fourDaysAgo, QA::AnswerRating::Correct)};
//    std::set<Day> periods{1, 6};
//    QARepeatPeriodChecker checker{periods};
//    ASSERT_TRUE(checker.ShouldBeRepeated(history));
//}

//TEST_F(QARepeatPeriodCheckerTestSuite, FourPeriodsGiven_FourHistoryGiven_shouldReturnFALSE)
//{
//    auto yesterday = QDate::currentDate().addDays(-1);
//    auto threeDaysAgo = QDate::currentDate().addDays(-3);
//    auto fourDaysAgo = QDate::currentDate().addDays(-4);
//    std::map<QDate, QA::AnswerRating> history{
//    std::make_pair(yesterday, QA::AnswerRating::Correct),
//                std::make_pair(threeDaysAgo, QA::AnswerRating::Correct),
//                std::make_pair(fourDaysAgo, QA::AnswerRating::Correct)};
//    std::set<Day> periods{1, 2, 4};
//    QARepeatPeriodChecker checker{periods};
//    ASSERT_FALSE(checker.ShouldBeRepeated(history));
//}


//TEST_F(QARepeatPeriodCheckerTestSuite, noHistoryItemGiven_ShouldReturnFalse)
//{
//    std::map<QDate, QA::AnswerRating> history;
//    std::set<Day> periods{1,2,14,30,90,180,360};
//    QARepeatPeriodChecker checker{periods};
//    ASSERT_FALSE(checker.ShouldBeRepeated(history));
//}

//TEST_F(QARepeatPeriodCheckerTestSuite, oneHistoryItemGiven_ShouldReturnTrue)
//{
//    std::map<QDate, QA::AnswerRating> history;
//    history[QDate(QDate::currentDate().year(),
//                  QDate::currentDate().month(),
//                  QDate::currentDate().day()-1)] = QA::AnswerRating::Correct;
//    std::set<Day> periods{1,2,14,30,90,180,360};
//    QARepeatPeriodChecker checker{periods};
//    ASSERT_TRUE(checker.ShouldBeRepeated(history));
//}

//TEST_F(QARepeatPeriodCheckerTestSuite, TwoHistoryItemGiven_ShouldReturnTrue)
//{
//    std::map<QDate, QA::AnswerRating> history;
//    history[QDate(QDate::currentDate().year(),
//                  QDate::currentDate().month(),
//                  QDate::currentDate().day()-2)] = QA::AnswerRating::Correct;

//    history[QDate(QDate::currentDate().year(),
//                  QDate::currentDate().month(),
//                  QDate::currentDate().day()-1)] = QA::AnswerRating::Correct;

//    std::set<Day> periods{1,2,14,30,90,180,360};
//    QARepeatPeriodChecker checker{periods};
//    ASSERT_TRUE(checker.ShouldBeRepeated(history));
//}

//TEST_F(QARepeatPeriodCheckerTestSuite, TwoHistoryItemGivenWithTodayDate_ShouldReturnFalse)
//{
//    std::map<QDate, QA::AnswerRating> history;
//    history[QDate(QDate::currentDate().year(),
//                  QDate::currentDate().month(),
//                  QDate::currentDate().day()-1)] = QA::AnswerRating::Correct;
//    history[QDate::currentDate()] = QA::AnswerRating::Correct;

//    std::set<Day> periods{1,2,7,14,30,90,180,360};
//    QARepeatPeriodChecker checker{periods};
//    ASSERT_FALSE(checker.ShouldBeRepeated(history));
//}
