#include <memory>
#include "../gtest.h"
#include "../gmock.h"
#include "../../GonzalesApp/qa/QAsSelection/Selectors/Utils/QARepeatPeriodChecker.h"
#include "QAToViewConverterMock.h"
#include "../Teacher/QAViewMock.h"
#include "../../GonzalesApp/qa/QAsSelection/Selectors/QAsNotLearnedSelector.h"
#include "../../GonzalesApp/qa/QASimpleView.h"

using namespace testing;

class QAsNotLearnedTestSuite: public testing::Test
{
protected:
    std::shared_ptr<StrictMock<QAToViewConverterMock>> converterMock = std::make_shared<StrictMock<QAToViewConverterMock>>();
    QAsNotLearnedSelector selector{converterMock};
};

TEST_F(QAsNotLearnedTestSuite, EmptyQAsGiven_ShouldSelectNothing)
{
    std::vector<std::shared_ptr<QA>> qas;
    ASSERT_TRUE(selector.select(qas).empty());
}

TEST_F(QAsNotLearnedTestSuite, OneQAsGivenWithCorrectedAnsweredQuestion_ShouldSelectNothing)
{
    std::shared_ptr<QA> qa = std::make_shared<QA>();
    qa->answersHistory.insert(std::make_pair(QDate::currentDate(), QA::AnswerRating::Correct));

    std::vector<std::shared_ptr<QA>> qas{qa};
    ASSERT_TRUE(selector.select(qas).empty());
}

TEST_F(QAsNotLearnedTestSuite, OneQAsGivenWithIncorrectAnsweredQuestion_ShouldSelectOneQA)
{
    std::shared_ptr<QA> qa = std::make_shared<QA>();
    qa->answersHistory.insert(std::make_pair(QDate::currentDate().addDays(-1), QA::AnswerRating::Correct));
    qa->answersHistory.insert(std::make_pair(QDate::currentDate(), QA::AnswerRating::Incorrect));

    std::shared_ptr<QAViewMock> mock = std::make_shared<QAViewMock>();
    EXPECT_CALL(*converterMock, convert(qa)).WillOnce(Return(mock));
    std::vector<std::shared_ptr<QA>> qas{qa};
    ASSERT_EQ(1, selector.select(qas).size());
}

TEST_F(QAsNotLearnedTestSuite, TwoQAsGivenWithIncorrectAnsweredQuestion_ShouldSelectOneQA)
{
    std::shared_ptr<QA> qa1 = std::make_shared<QA>();
    qa1->answersHistory.insert(std::make_pair(QDate::currentDate().addDays(-1), QA::AnswerRating::Correct));
    qa1->answersHistory.insert(std::make_pair(QDate::currentDate(), QA::AnswerRating::Incorrect));

    std::shared_ptr<QA> qa2 = std::make_shared<QA>();
    std::shared_ptr<QAViewMock> mock = std::make_shared<QAViewMock>();
    EXPECT_CALL(*converterMock, convert(qa1)).WillOnce(Return(mock));
    std::vector<std::shared_ptr<QA>> qas{qa1, qa2};
    ASSERT_EQ(1, selector.select(qas).size());
}


