#include <memory>
#include "../gtest.h"
#include "../gmock.h"
#include "../../GonzalesApp/qa/QAsSelection/QAsSelector.h"

using namespace testing;

class QAsSelectorTestSuite: public testing::Test
{
protected:
    QAsSelector selector = QAsSelector(0.60, 10);
    std::shared_ptr<QA> newQAs = std::make_shared<QA>();
};

TEST_F(QAsSelectorTestSuite, NoQuestionGiven_SelectorShouldSelectNothing)
{
    auto emptyVec = std::vector<std::shared_ptr<QA>>();
    auto selectedQAs = selector.select(emptyVec);
    EXPECT_EQ(0, selectedQAs.size());
}

TEST_F(QAsSelectorTestSuite, _10NewQuestionsGiven_10QuestionShouldBeSelected)
{
    std::vector<std::shared_ptr<QA>> qas{newQAs, newQAs,
                                     newQAs, newQAs,
                                     newQAs, newQAs,
                                     newQAs, newQAs,
                                     newQAs, newQAs};
    auto selectedQAs = selector.select(qas);
    EXPECT_EQ(6, selectedQAs.size());
}


TEST_F(QAsSelectorTestSuite, _2New_Max2__ShouldSelect2)
{
    QAsSelector selector = QAsSelector(0.60, 2);
    std::vector<std::shared_ptr<QA>> qas{newQAs, newQAs};
    auto selectedQAs = selector.select(qas);
    EXPECT_EQ(2, selectedQAs.size());
}

TEST_F(QAsSelectorTestSuite, _2New_Max5__ShouldSelect2)
{
    QAsSelector selector = QAsSelector(0.60, 2);
    std::vector<std::shared_ptr<QA>> qas{newQAs, newQAs, newQAs, newQAs, newQAs};
    auto selectedQAs = selector.select(qas);
    EXPECT_EQ(2, selectedQAs.size());
}

TEST_F(QAsSelectorTestSuite, _11New_Max10__ShouldSelect10)
{
    std::vector<std::shared_ptr<QA>> qas{newQAs, newQAs,
                                         newQAs, newQAs,
                                         newQAs, newQAs,
                                         newQAs, newQAs,
                                         newQAs, newQAs,
                                         newQAs};
    auto selectedQAs = selector.select(qas);
    EXPECT_EQ(6, selectedQAs.size());
}

bool isOldQA(const std::shared_ptr<QA>& qa)
{
    return !qa->getAnswersHistory().empty();
}

TEST_F(QAsSelectorTestSuite, _10New_10Old_Max10_NewFactor06__ShouldSelect6new4old)
{
    QDateTime dateTime(QDate::currentDate(), QTime::currentTime());
    std::shared_ptr<QA> oldQa = std::make_shared<QA>();
    oldQa->addHistoryEntry(dateTime, QA::AnswerRating::Correct);

    std::shared_ptr<QA> newQa = std::make_shared<QA>();

    std::vector<std::shared_ptr<QA>> qas{oldQa, oldQa, oldQa, oldQa, oldQa, oldQa, oldQa, oldQa, oldQa, oldQa,
                                         newQa, newQa, newQa, newQa, newQa, newQa, newQa, newQa, newQa, newQa};

    auto selectedQAs = selector.select(qas);

    EXPECT_EQ(10, selectedQAs.size());
    auto bound = std::partition(selectedQAs.begin(), selectedQAs.end(), isOldQA);
    EXPECT_EQ(4, std::distance(selectedQAs.begin(), bound));
    EXPECT_EQ(6, std::distance(bound, selectedQAs.end()));
}

TEST_F(QAsSelectorTestSuite, _10New_10Old_Max10_NewFactor06__ShouldSelect6new4oldWrongAnswered)
{
    QDateTime dateTime(QDate::currentDate(), QTime::currentTime());
    std::shared_ptr<QA> oldQaCorrectAnswered = std::make_shared<QA>();
    oldQaCorrectAnswered->addHistoryEntry(dateTime, QA::AnswerRating::Correct);

    std::shared_ptr<QA> oldQaWrongAnswered = std::make_shared<QA>();
    oldQaCorrectAnswered->addHistoryEntry(dateTime, QA::AnswerRating::Incorrect);


    std::shared_ptr<QA> newQa = std::make_shared<QA>();

    std::vector<std::shared_ptr<QA>> qas{oldQaCorrectAnswered, oldQaCorrectAnswered,
                                         oldQaCorrectAnswered, oldQaWrongAnswered,
                                         oldQaWrongAnswered, oldQaWrongAnswered,
                                         oldQaCorrectAnswered, oldQaCorrectAnswered,
                                         oldQaCorrectAnswered, oldQaWrongAnswered,
                                         newQa, newQa, newQa, newQa, newQa,
                                         newQa, newQa, newQa, newQa, newQa};

    auto selectedQAs = selector.select(qas);

    int allQAs = 10;
    int newQAs = 6;
    int oldQAs = 4;

    EXPECT_EQ(allQAs, selectedQAs.size());
    auto oldQAsBound = std::partition(selectedQAs.begin(), selectedQAs.end(), isOldQA);
    EXPECT_EQ(oldQAs, std::distance(selectedQAs.begin(), oldQAsBound));
    EXPECT_EQ(newQAs, std::distance(oldQAsBound, selectedQAs.end()));

    auto goodAnsweredBound = std::find_if(selectedQAs.begin(), oldQAsBound,
                                     [](const std::shared_ptr<QA>& qa)
                                       {return !qa->wasWrongAnswered();});
    EXPECT_EQ(oldQAsBound, goodAnsweredBound);
}
