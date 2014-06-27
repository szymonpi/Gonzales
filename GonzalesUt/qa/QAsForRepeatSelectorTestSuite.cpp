#include <memory>
#include "../gtest.h"
#include "../gmock.h"
#include "../../GonzalesApp/qa/QAsSelection/QAsForRepeatSelector.h"
#include "QAsDestinationSelectorMock.h"
#include "QAsRepositoryMock.h"

using namespace testing;

class QAsForRepeatSelectorTestSuite: public testing::Test
{
protected:

};

TEST_F(QAsForRepeatSelectorTestSuite, EmptyQAsGiven_ShouldSelectNothing)
{
    std::vector<std::shared_ptr<QA>> qas;
    QAsForRepeatSelector selector;
    ASSERT_TRUE(selector.select(qas).empty());
}

TEST_F(QAsForRepeatSelectorTestSuite, OneQAsGivenWithOneIncorrectHistoryItem_ShouldSelectOneItem)
{
    std::vector<std::shared_ptr<QA>> qas;
    std::shared_ptr<QA> qa = std::make_shared<QA>();
    qa->answersHistory.emplace(QDate::currentDate(), QA::AnswerRating::Incorrect);

    qas.push_back(qa);
    QAsForRepeatSelector selector;
    ASSERT_EQ(1, selector.select(qas).size());
}

TEST_F(QAsForRepeatSelectorTestSuite, OneQAsGivenWithOneCorrectHistoryItemInRepeatPeriod_ShouldSelectOneItem)
{
    std::vector<std::shared_ptr<QA>> qas;
    std::shared_ptr<QA> qa = std::make_shared<QA>();
    QDate yesterday = QDate(QDate::currentDate().year(), QDate::currentDate().month(), QDate::currentDate().day()-1);
    qa->answersHistory.emplace(yesterday, QA::AnswerRating::Correct);

    qas.push_back(qa);

    std::vector<Days> periods{1};
    QAsForRepeatSelector selector{periods};
    ASSERT_EQ(1, selector.select(qas).size());
}
