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
    QAsForRepeatSelector selector{m_repeatPeriodChecker};
    ASSERT_TRUE(selector.select(qas).empty());
}

