#include <memory>
#include "../gtest.h"
#include "../gmock.h"
#include "../../GonzalesApp/qa/QAsSelection/QAsSelector.h"

using namespace testing;

class QAsSelectorTestSuite: public testing::Test
{
protected:
    QAsSelector selector = QAsSelector(0.60, 10);
};

TEST_F(QAsSelectorTestSuite, NoQuestionGiven_SelectorShouldSelectNothing)
{
    auto selectedQAs = selector.select(std::vector<std::shared_ptr<QA>>());
    EXPECT_EQ(0, selectedQAs.size());
}

TEST_F(QAsSelectorTestSuite, _10NewQuestionsGiven_10QuestionShouldBeSelected)
{
    std::vector<std::shared_ptr<QA>> qas{std::make_shared<QA>(), std::make_shared<QA>(),
                                     std::make_shared<QA>(), std::make_shared<QA>(),
                                     std::make_shared<QA>(), std::make_shared<QA>(),
                                     std::make_shared<QA>(), std::make_shared<QA>(),
                                     std::make_shared<QA>(), std::make_shared<QA>()};
    auto selectedQAs = selector.select(qas);
    EXPECT_EQ(10, selectedQAs.size());
}

TEST_F(QAsSelectorTestSuite, _11New_Max10__ShouldSelect10)
{
    std::vector<std::shared_ptr<QA>> qas{std::make_shared<QA>(), std::make_shared<QA>(),
                                     std::make_shared<QA>(), std::make_shared<QA>(),
                                     std::make_shared<QA>(), std::make_shared<QA>(),
                                     std::make_shared<QA>(), std::make_shared<QA>(),
                                     std::make_shared<QA>(), std::make_shared<QA>(),
                                     std::make_shared<QA>()};
    auto selectedQAs = selector.select(qas);
    EXPECT_EQ(10, selectedQAs.size());
}
