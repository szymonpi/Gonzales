#include <memory>
#include "../gtest.h"
#include "../gmock.h"
#include "../../GonzalesApp/qa/QAsSelection/QAsSelector.h"
#include <functional>

using namespace testing;

class QAsSelectorTestSuite: public testing::Test
{
protected:
    QAsSelectorTestSuite()
    {
        m_oldQA_One_Incorrect_HistoryEntry->addHistoryEntry(QDateTime::currentDateTime(), QA::AnswerRating::Incorrect);
        m_oldQA_One_Correct_HistoryEntry->addHistoryEntry(QDateTime::currentDateTime(), QA::AnswerRating::Correct);
    }

    QAsSelector selector = QAsSelector(0.60, 10);
    std::shared_ptr<QA> m_newQA = std::make_shared<QA>();
    std::shared_ptr<QA> m_oldQA_One_Incorrect_HistoryEntry = std::make_shared<QA>();
    std::shared_ptr<QA> m_oldQA_One_Correct_HistoryEntry = std::make_shared<QA>();
    std::function<bool(const std::shared_ptr<QA>& qa)> m_isOldQA = [](const std::shared_ptr<QA>& qa){ return !qa->getAnswersHistory().empty();};
};

TEST_F(QAsSelectorTestSuite, NoQuestionGiven_SelectorShouldSelectNothing)
{
    auto emptyVec = std::vector<std::shared_ptr<QA>>();
    auto selectedQAs = selector.select(emptyVec);
    EXPECT_EQ(0, selectedQAs.size());
}

TEST_F(QAsSelectorTestSuite, _10NewQuestionsGiven_10QuestionShouldBeSelected)
{
    std::vector<std::shared_ptr<QA>> qas{m_newQA, m_newQA,
                                     m_newQA, m_newQA,
                                     m_newQA, m_newQA,
                                     m_newQA, m_newQA,
                                     m_newQA, m_newQA};
    auto selectedQAs = selector.select(qas);
    EXPECT_EQ(6, selectedQAs.size());
}


TEST_F(QAsSelectorTestSuite, _2New_Max2__ShouldSelect2)
{
    QAsSelector selector = QAsSelector(0.60, 2);
    std::vector<std::shared_ptr<QA>> qas{m_newQA, m_newQA};
    auto selectedQAs = selector.select(qas);
    EXPECT_EQ(2, selectedQAs.size());
}

TEST_F(QAsSelectorTestSuite, _2New_Max5__ShouldSelect2)
{
    QAsSelector selector = QAsSelector(0.60, 2);
    std::vector<std::shared_ptr<QA>> qas{m_newQA, m_newQA, m_newQA, m_newQA, m_newQA};
    auto selectedQAs = selector.select(qas);
    EXPECT_EQ(2, selectedQAs.size());
}

TEST_F(QAsSelectorTestSuite, _11New_Max10__ShouldSelect10)
{
    std::vector<std::shared_ptr<QA>> qas{m_newQA, m_newQA,
                                         m_newQA, m_newQA,
                                         m_newQA, m_newQA,
                                         m_newQA, m_newQA,
                                         m_newQA, m_newQA,
                                         m_newQA};
    auto selectedQAs = selector.select(qas);
    EXPECT_EQ(6, selectedQAs.size());
}

TEST_F(QAsSelectorTestSuite, _10New_10Old_Max10_NewFactor06__ShouldSelect6new4old)
{
    std::vector<std::shared_ptr<QA>> qas{m_oldQA_One_Incorrect_HistoryEntry, m_oldQA_One_Incorrect_HistoryEntry, m_oldQA_One_Incorrect_HistoryEntry,
                                         m_oldQA_One_Incorrect_HistoryEntry, m_oldQA_One_Incorrect_HistoryEntry, m_oldQA_One_Incorrect_HistoryEntry,
                                         m_oldQA_One_Incorrect_HistoryEntry, m_oldQA_One_Incorrect_HistoryEntry, m_oldQA_One_Incorrect_HistoryEntry, m_oldQA_One_Incorrect_HistoryEntry,
                                         m_newQA, m_newQA, m_newQA, m_newQA, m_newQA, m_newQA, m_newQA, m_newQA, m_newQA, m_newQA};

    auto selectedQAs = selector.select(qas);

    EXPECT_EQ(10, selectedQAs.size());
    auto bound = std::partition(selectedQAs.begin(), selectedQAs.end(), m_isOldQA);
    EXPECT_EQ(4, std::distance(selectedQAs.begin(), bound));
    EXPECT_EQ(6, std::distance(bound, selectedQAs.end()));
}

TEST_F(QAsSelectorTestSuite, _10New_10Old_Max10_NewFactor06__ShouldSelect6new4oldWrongAnswered)
{

    std::vector<std::shared_ptr<QA>> qas{m_oldQA_One_Correct_HistoryEntry, m_oldQA_One_Correct_HistoryEntry,
                                         m_oldQA_One_Correct_HistoryEntry, m_oldQA_One_Incorrect_HistoryEntry,
                                         m_oldQA_One_Incorrect_HistoryEntry, m_oldQA_One_Incorrect_HistoryEntry,
                                         m_oldQA_One_Correct_HistoryEntry, m_oldQA_One_Correct_HistoryEntry,
                                         m_oldQA_One_Correct_HistoryEntry, m_oldQA_One_Incorrect_HistoryEntry,
                                         m_newQA, m_newQA, m_newQA, m_newQA, m_newQA,
                                         m_newQA, m_newQA, m_newQA, m_newQA, m_newQA};

    auto selectedQAs = selector.select(qas);

    int allQAs = 10;
    int m_newQA = 6;
    int oldQAs = 4;

    EXPECT_EQ(allQAs, selectedQAs.size());

    auto oldQasBegin = selectedQAs.begin();
    auto oldQAsEnd = std::partition(selectedQAs.begin(), selectedQAs.end(), m_isOldQA);
    auto newQAsBegin = oldQAsEnd;
    auto newQAsEnd = selectedQAs.end();

    EXPECT_EQ(oldQAs, std::distance(oldQasBegin, oldQAsEnd));
    EXPECT_EQ(m_newQA, std::distance(newQAsBegin, newQAsEnd));

    auto wrongAnsweredBegin = selectedQAs.begin();
    auto wrongAnsweredEnd = std::find_if(wrongAnsweredBegin, oldQAsEnd,
                                     [](const std::shared_ptr<QA>& qa)
                                       {return !qa->wasWrongAnswered();});
    EXPECT_EQ(oldQAsEnd, wrongAnsweredEnd);
}

TEST_F(QAsSelectorTestSuite, _10New_10Old_Max10_NewFactor06_oldShouldByWrongAnsweredDate__ShouldSelect6new4oldWrongAnswered)
{

    std::vector<std::shared_ptr<QA>> qas{m_oldQA_One_Correct_HistoryEntry, m_oldQA_One_Correct_HistoryEntry,
                                         m_oldQA_One_Correct_HistoryEntry, m_oldQA_One_Incorrect_HistoryEntry,
                                         m_oldQA_One_Incorrect_HistoryEntry, m_oldQA_One_Incorrect_HistoryEntry,
                                         m_oldQA_One_Correct_HistoryEntry, m_oldQA_One_Correct_HistoryEntry,
                                         m_oldQA_One_Correct_HistoryEntry, m_oldQA_One_Incorrect_HistoryEntry,
                                         m_newQA, m_newQA, m_newQA, m_newQA, m_newQA,
                                         m_newQA, m_newQA, m_newQA, m_newQA, m_newQA};

    auto selectedQAs = selector.select(qas);

    int allQAs = 10;
    int m_newQA = 6;
    int oldQAs = 4;

    EXPECT_EQ(allQAs, selectedQAs.size());

    auto oldQasBegin = selectedQAs.begin();
    auto oldQAsEnd = std::partition(selectedQAs.begin(), selectedQAs.end(), m_isOldQA);
    auto newQAsBegin = oldQAsEnd;
    auto newQAsEnd = selectedQAs.end();

    EXPECT_EQ(oldQAs, std::distance(oldQasBegin, oldQAsEnd));
    EXPECT_EQ(m_newQA, std::distance(newQAsBegin, newQAsEnd));

    auto wrongAnsweredBegin = selectedQAs.begin();
    auto wrongAnsweredEnd = std::find_if(wrongAnsweredBegin, oldQAsEnd,
                                     [](const std::shared_ptr<QA>& qa)
                                       {return !qa->wasWrongAnswered();});
    EXPECT_EQ(oldQAsEnd, wrongAnsweredEnd);
}
