#include <memory>
#include "../gtest.h"
#include "../gmock.h"
#include "../../GonzalesApp/qa/QAsSelection/Selectors/Utils/QARepeatPeriodChecker.h"
#include "QAsDestinationSelectorMock.h"
#include "QAsRepositoryMock.h"
#include "QAToViewConverterMock.h"
#include "../Teacher/QAViewMock.h"
#include "../../GonzalesApp/qa/QAsSelection/Selectors/QAsForRepeatSelector.h"
#include "QARepeatPeriodCheckerMock.h"

using namespace testing;

class QAsForRepeatSelectorTestSuite: public testing::Test
{
protected:
    std::shared_ptr<StrictMock<QAToViewConverterMock>> m_converterMock = std::make_shared<StrictMock<QAToViewConverterMock>>();
    std::shared_ptr<StrictMock<QARepeatPeriodCheckerMock>> m_repeatPeriodChecker = std::make_shared<StrictMock<QARepeatPeriodCheckerMock>>();
};

TEST_F(QAsForRepeatSelectorTestSuite, EmptyQAsGiven_ShouldSelectNothing)
{
    std::vector<std::shared_ptr<QA>> qas;
    QAsForRepeatSelector selector{m_converterMock, m_repeatPeriodChecker};
    ASSERT_TRUE(selector.select(qas).empty());
}

TEST_F(QAsForRepeatSelectorTestSuite, OneQAsGivenWithOneIncorrectHistoryItem_ShouldntSelectItem)
{
    std::vector<std::shared_ptr<QA>> qas;
    std::shared_ptr<QA> qa = std::make_shared<QA>();
    qa->answersHistory.emplace(QDate::currentDate(), QA::AnswerRating::Incorrect);
    auto m_view = std::make_shared<QAViewMock>();
    EXPECT_CALL(*m_converterMock, convert(_)).WillOnce(Return(m_view));
    EXPECT_CALL(*m_repeatPeriodChecker, shouldBeRepeated(_)).WillOnce(Return(true));

    qas.push_back(qa);
    QAsForRepeatSelector selector{m_converterMock, m_repeatPeriodChecker};
    ASSERT_EQ(0, selector.select(qas).size());
}

TEST_F(QAsForRepeatSelectorTestSuite, OneQAsGivenWithOneCorrectHistoryItemInRepeatPeriod_ShouldSelectOneItem)
{
    std::vector<std::shared_ptr<QA>> qas;
    std::shared_ptr<QA> qa = std::make_shared<QA>();
    QDate yesterday = QDate(QDate::currentDate().year(), QDate::currentDate().month(), QDate::currentDate().day()-1);
    qa->answersHistory[yesterday] = QA::AnswerRating::Correct;
    auto m_view = std::make_shared<QAViewMock>();
    EXPECT_CALL(*m_converterMock, convert(_)).WillOnce(Return(m_view));
    EXPECT_CALL(*m_repeatPeriodChecker, shouldBeRepeated(_)).WillOnce(Return(true));

    qas.push_back(qa);

    QAsForRepeatSelector selector{m_converterMock, m_repeatPeriodChecker};
    ASSERT_EQ(1, selector.select(qas).size());
}

TEST_F(QAsForRepeatSelectorTestSuite, DISABLED_OneQAsGiven_WithOneCorrectHistoryItemNotInRepeatPeriod_ShouldSelectOneItem)
{
    std::vector<std::shared_ptr<QA>> qas;
    std::shared_ptr<QA> qa = std::make_shared<QA>();
    QDate twodaysAgo = QDate(QDate::currentDate().year(), QDate::currentDate().month(), QDate::currentDate().day()-1);
    qa->answersHistory[twodaysAgo] = QA::AnswerRating::Correct;

    qas.push_back(qa);

    QAsForRepeatSelector selector{m_converterMock, m_repeatPeriodChecker};
    ASSERT_EQ(0, selector.select(qas).size());
}
