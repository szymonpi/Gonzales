
#include <memory>
#include "../gtest.h"
#include "../gmock.h"
#include"../../GonzalesApp/qa/QALearnedChecker.h"
#include "../../GonzalesApp/qa/QA.h"

using namespace testing;

class QALearnedCheckerTestSuite: public testing::Test
{
public:

};

TEST_F(QALearnedCheckerTestSuite, QAWithNoAnswerHistoryGiven_ShouldReturnFalse)
{
    QA question;
    QALearnedChecker checker;
    ASSERT_FALSE(checker.isLearned(question));
}

TEST_F(QALearnedCheckerTestSuite, QAWithOneIncorrectAnswerHistoryEntry_ShouldReturnFalse)
{
    QA question;
    question.answersHistory.emplace(QDate::currentDate(), QA::AnswerRating::Incorrect);
    QALearnedChecker checker;
    ASSERT_FALSE(checker.isLearned(question));
}

TEST_F(QALearnedCheckerTestSuite, QAWithOneCorrectAnswerHistoryEntry_ShouldReturnTrue)
{
    QA question;
    question.answersHistory.emplace(QDate::currentDate(), QA::AnswerRating::Correct);
    QALearnedChecker checker;
    ASSERT_TRUE(checker.isLearned(question));
}

