#include <memory>
#include "../gtest.h"
#include "../gmock.h"
#include "../../GonzalesApp/qa/QAMarker.h"
#include "QAsDestinationSelectorMock.h"
#include "QAsRepositoryMock.h"
#include <ostream>
#include <QAsRepositoryMock.h>

using namespace testing;

void PrintTo(const QDate &date, std::ostream* os)
{
    *os << date.toString("dd.MM.yyyy").toStdString();
}

void PrintTo(const QA::AnswerRating &answerRating, std::ostream* os)
{
    if(answerRating == QA::AnswerRating::Correct)
        *os << "Correct";
    else
        *os << "Incorrect";
}

class QAMarkerSuite: public testing::Test
{
public:
    std::shared_ptr<StrictMock<QAsRepositoryMock>> m_qaRepositoryMock =
                std::make_shared<StrictMock<QAsRepositoryMock>>();
};

TEST_F(QAMarkerSuite, QuestionGiven_ShouldMarkAsKnown)
{
    QA qa;
    QAMarker marker(m_qaRepositoryMock);
    QDate currentDateTime = QDate::currentDate();
    EXPECT_CALL(*m_qaRepositoryMock, onQAsUpdate());
    marker.markAsKnown(qa);

    auto history = qa.getAnswersHistory();
    ASSERT_EQ(1, history.size());
    EXPECT_GE(history.begin()->first, currentDateTime);
    EXPECT_EQ(history.begin()->second, QA::AnswerRating::Correct);
}

TEST_F(QAMarkerSuite, QuestionGiven_ShouldMarkAsUnknown)
{
    QA qa;
    QAMarker marker(m_qaRepositoryMock);
    QDate currentDateTime = QDate::currentDate();
    EXPECT_CALL(*m_qaRepositoryMock, onQAsUpdate());
    marker.markAsUnknown(qa);

    auto history = qa.getAnswersHistory();
    ASSERT_EQ(1, history.size());
    EXPECT_GE(history.begin()->first, currentDateTime);
    EXPECT_EQ(history.begin()->second, QA::AnswerRating::Incorrect);
}

TEST_F(QAMarkerSuite, QuestionGivenWithOneIncorrectMarkedToday_ShouldMarkAsUnknown)
{
    QA qa;
    qa.answersHistory.emplace(QDate::currentDate(), QA::AnswerRating::Incorrect);
    QAMarker marker(m_qaRepositoryMock);
    QDate currentDateTime = QDate::currentDate();
    EXPECT_CALL(*m_qaRepositoryMock, onQAsUpdate());
    marker.markAsUnknown(qa);

    auto history = qa.getAnswersHistory();
    ASSERT_EQ(1, history.size());
    EXPECT_GE(history.begin()->first, currentDateTime);
    EXPECT_EQ(history.begin()->second, QA::AnswerRating::Incorrect);
}

TEST_F(QAMarkerSuite, QuestionGivenWithOneCorrectMarkedToday_MarkAsUnknownShuldMarkAsUnknown)
{
    QA qa;
    qa.answersHistory[QDate::currentDate()] = QA::AnswerRating::Correct;
    QAMarker marker(m_qaRepositoryMock);
    QDate currentDateTime = QDate::currentDate();
    EXPECT_CALL(*m_qaRepositoryMock, onQAsUpdate());
    marker.markAsUnknown(qa);

    auto history = qa.getAnswersHistory();
    ASSERT_EQ(1, history.size());
    EXPECT_GE(history.begin()->first, currentDateTime);
    EXPECT_EQ(history.begin()->second, QA::AnswerRating::Incorrect);
}

TEST_F(QAMarkerSuite, QuestionGivenWithOneIncorrectMarkedToday_MarkAsKnownShuldMarkAsUnknown)
{
    QA qa;
    qa.answersHistory.emplace(QDate::currentDate(), QA::AnswerRating::Incorrect);
    QAMarker marker(m_qaRepositoryMock);
    QDate currentDateTime = QDate::currentDate();
    EXPECT_CALL(*m_qaRepositoryMock, onQAsUpdate());
    marker.markAsKnown(qa);

    auto history = qa.getAnswersHistory();
    ASSERT_EQ(1, history.size());
    EXPECT_GE(history.begin()->first, currentDateTime);
    EXPECT_EQ(history.begin()->second, QA::AnswerRating::Incorrect);
}

TEST_F(QAMarkerSuite, QuestionGivenWithOneCorrectMarkedToday_MarkAsKnownShuldAddOneNewEntry)
{
    QA qa;
    qa.answersHistory.emplace(QDate(2010, 10, 4), QA::AnswerRating::Incorrect);
    QAMarker marker(m_qaRepositoryMock);
    EXPECT_CALL(*m_qaRepositoryMock, onQAsUpdate());
    QDate currentDateTime = QDate::currentDate();
    marker.markAsKnown(qa);

    auto history = qa.getAnswersHistory();
    ASSERT_EQ(2, history.size());
    EXPECT_EQ(history.begin()->first, QDate(2010, 10, 4));
    EXPECT_EQ(history.begin()->second, QA::AnswerRating::Incorrect);
    EXPECT_GE((++history.begin())->first, currentDateTime);
    EXPECT_EQ((++history.begin())->second, QA::AnswerRating::Correct);
}
