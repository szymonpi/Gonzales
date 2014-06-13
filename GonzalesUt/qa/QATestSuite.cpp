
#include <memory>
#include "../gtest.h"
#include "../gmock.h"
#include "../../GonzalesApp/qa/QA.h"
#include "../AQImporter/DataSerializerMock.h"
#include "../AQImporter/DataDeserializerMock.h"
#include "../CommonUtUtilities/PrintTo.h"
#include <map>

using namespace testing;

class QATestSuite: public testing::Test
{
protected:
    StrictMock<DataDeserializerMock> deserializerMock;
    StrictMock<DataSerializerMock> serializerMock;
    QString question = "question";
    QString answer = "answer";
    QA qa{Question{question}, Answer{answer}};
};


TEST_F(QATestSuite, noAnswersHistoryShouldReturnFalse)
{
    EXPECT_FALSE(qa.wasWrongAnswered());
}

TEST_F(QATestSuite, noWrongAnsweredShouldReturnFalse)
{
    qa.addHistoryEntry(QDate::currentDate(), QA::AnswerRating::Correct);
    EXPECT_FALSE(qa.wasWrongAnswered());
}

TEST_F(QATestSuite, noWrongAnsweredShouldReturnTrue)
{
    qa.addHistoryEntry(QDate::currentDate(), QA::AnswerRating::Correct);
    qa.addHistoryEntry(QDate::currentDate(), QA::AnswerRating::Incorrect);
    EXPECT_TRUE(qa.wasWrongAnswered());
}

TEST_F(QATestSuite, shouldSerializeQAWithoutAnswerHistory)
{
    EXPECT_CALL(serializerMock, serialize(TypedEq<const QString&>(question)));
    EXPECT_CALL(serializerMock, serialize(TypedEq<const QString&>(answer)));
    EXPECT_CALL(serializerMock, serialize(TypedEq<std::size_t>(0)));
    qa.serialize(serializerMock);
}

TEST_F(QATestSuite, shouldSerializeQAWithAnswerHistory)
{
    unsigned ExpectedAnswerRating = unsigned(QA::AnswerRating::Correct);
    int expectedAnswerHistorySize = 1;
    QDate dateTime(2014, 5, 6);


    qa.addHistoryEntry(dateTime, QA::AnswerRating(ExpectedAnswerRating));

    EXPECT_CALL(serializerMock, serialize(TypedEq<const QString&>(question)));
    EXPECT_CALL(serializerMock, serialize(TypedEq<const QString&>(answer)));
    EXPECT_CALL(serializerMock, serialize(TypedEq<std::size_t>(expectedAnswerHistorySize)));

    EXPECT_CALL(serializerMock, serialize(TypedEq<unsigned>(ExpectedAnswerRating)));
    EXPECT_CALL(serializerMock, serialize(TypedEq<const QDate &>(dateTime)));

    qa.serialize(serializerMock);
}

TEST_F(QATestSuite, shouldDeserializeQAWithoutAnswerHistory)
{
    QString question = "question";
    QString answer = "answer";
    std::size_t answerHistorySize = 0;

    EXPECT_CALL(deserializerMock, deserialize(An<QString&>()))
            .WillOnce(SetArgReferee<0>(question))
            .WillOnce(SetArgReferee<0>(answer));

    EXPECT_CALL(deserializerMock, deserialize(An<int&>())).WillOnce(SetArgReferee<0>(answerHistorySize));
    qa.deserialize(deserializerMock);
}

TEST_F(QATestSuite, shouldDeserializeQAWithAnswerHistory)
{
    QString question = "question";
    QString answer = "answer";
    std::size_t answerHistorySize = 1;
    unsigned answerRating = unsigned(QA::AnswerRating::Correct);
    QDate m_date;

    EXPECT_CALL(deserializerMock, deserialize(An<QString&>()))
            .WillOnce(SetArgReferee<0>(question))
            .WillOnce(SetArgReferee<0>(answer));

    EXPECT_CALL(deserializerMock, deserialize(An<unsigned&>())).WillOnce(SetArgReferee<0>(answerRating));
    EXPECT_CALL(deserializerMock, deserialize(An<int&>())).WillOnce(SetArgReferee<0>(answerHistorySize));
    EXPECT_CALL(deserializerMock, deserialize(An<QDate&>())).WillOnce(SetArgReferee<0>(m_date));

    qa.deserialize(deserializerMock);
}
