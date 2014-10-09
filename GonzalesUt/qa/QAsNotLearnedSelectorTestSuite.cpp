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
    isNotLearned selector{};
};

TEST_F(QAsNotLearnedTestSuite, EmptyQAsGiven_ShouldSelectNothing)
{
    std::shared_ptr<QA> qa = std::make_shared<QA>();
    ASSERT_FALSE(selector(qa));
}

TEST_F(QAsNotLearnedTestSuite, OneQAsGivenWithCorrectedAnsweredQuestion_ShouldSelectNothing)
{
    std::shared_ptr<QA> qa = std::make_shared<QA>();
    qa->answersHistory.insert(std::make_pair(QDate::currentDate(), QA::AnswerRating::Correct));

    ASSERT_FALSE(selector(qa));
}

TEST_F(QAsNotLearnedTestSuite, OneQAsGivenWithIncorrectAnsweredQuestion_ShouldSelectOneQA)
{
    std::shared_ptr<QA> qa = std::make_shared<QA>();
    qa->answersHistory.insert(std::make_pair(QDate::currentDate().addDays(-1), QA::AnswerRating::Correct));
    qa->answersHistory.insert(std::make_pair(QDate::currentDate(), QA::AnswerRating::Incorrect));

    ASSERT_TRUE(selector(qa));
}
