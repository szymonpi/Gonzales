#include <memory>
#include "../gtest.h"
#include "../gmock.h"
#include "../../GonzalesApp/qa/QAMarker.h"
#include "QAsDestinationSelectorMock.h"
#include "QAsRepositoryMock.h"
#include <ostream>
#include <QAsRepositoryMock.h>

using namespace testing;

void PrintTo(const QDateTime &dateTime, std::ostream* os)
{
    *os << dateTime.toString("dd.MM.yyyy::hh:mm:ss.zzz").toStdString();
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
    QDateTime currentDateTime = QDateTime::currentDateTime();
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
    QDateTime currentDateTime = QDateTime::currentDateTime();
    EXPECT_CALL(*m_qaRepositoryMock, onQAsUpdate());
    marker.markAsUnknown(qa);

    auto history = qa.getAnswersHistory();
    ASSERT_EQ(1, history.size());
    EXPECT_GE(history.begin()->first, currentDateTime);
    EXPECT_EQ(history.begin()->second, QA::AnswerRating::Incorrect);
}
