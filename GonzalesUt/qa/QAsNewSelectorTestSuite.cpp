
#include <memory>
#include "../gtest.h"
#include "../gmock.h"
#include "../../GonzalesApp/qa/QAsSelection/Selectors/Utils/QARepeatPeriodChecker.h"
#include "QAToViewConverterMock.h"
#include "../Teacher/QAViewMock.h"
#include "../../GonzalesApp/qa/QAsSelection/Selectors/QAsNewSelector.h"

using namespace testing;

class QAsNewSelectorTestSuite: public testing::Test
{
protected:
    std::shared_ptr<StrictMock<QAToViewConverterMock>> converterMock = std::make_shared<StrictMock<QAToViewConverterMock>>();
    QAsNewSelector selector{};
};

TEST_F(QAsNewSelectorTestSuite, EmptyQAsGiven_ShouldSelectNothing)
{
    std::vector<std::shared_ptr<QA>> qas;
    ASSERT_TRUE(selector.select(qas).empty());
}

TEST_F(QAsNewSelectorTestSuite, OneNewQAGiven_ShouldSelectOne)
{
    std::vector<std::shared_ptr<QA>> qas{std::make_shared<QA>()};
    EXPECT_EQ(1, selector.select(qas).size());
}


