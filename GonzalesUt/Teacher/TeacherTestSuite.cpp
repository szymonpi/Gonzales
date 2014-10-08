#include <iostream>
#include "../gtest.h"
#include <../../GonzalesApp/teaching/Teacher.h>
#include <utility>
#include <memory>
#include <exception>
#include "PresentersMock.h"
#include "../qa/QAsRepositoryMock.h"
#include "QAsToLearnProviderMock.h"
#include "QAViewMock.h"

using namespace testing;

class TeacherTestSuite: public ::testing::Test
{

protected:
    TeacherTestSuite():
        m_questionPresenterMock(std::make_shared<QuestionPresenterMock>()),
        m_answerPresenterMock(std::make_shared<AnswerPresenterMock>()),
        m_qasProvider(std::make_shared<QAsToLearnProviderMock>())
    {

    }

    std::shared_ptr<QuestionPresenterMock> m_questionPresenterMock;
    std::shared_ptr<AnswerPresenterMock> m_answerPresenterMock;
    std::shared_ptr<QAsToLearnProviderMock> m_qasProvider;
    std::shared_ptr<Teacher> teacher;
    std::vector<QA> oneQuestionQueue;
    std::vector<QA> twoQuestionQueue;
    std::vector<QA> sixQuestionQueue;

};

TEST_F(TeacherTestSuite, QAsToLearnProviderReturnNoItem_ShouldThrow)
{

    EXPECT_CALL(*m_qasProvider, getQAs()).WillOnce(Return(QQueue<std::shared_ptr<QAView>>()));
    EXPECT_THROW(std::make_shared<Teacher>(m_qasProvider), std::logic_error);
}


TEST_F(TeacherTestSuite, QAsToLearnProviderReturnOne_ShouldPresentQuestion)
{
    QQueue<std::shared_ptr<QAView>> qas;
    auto qaView  = std::make_shared<StrictMock<QAViewMock>>();
    qas.push_back(qaView);
    EXPECT_CALL(*m_qasProvider, getQAs()).WillOnce(Return(qas));
    teacher = std::make_shared<Teacher>(m_qasProvider);

    EXPECT_CALL(*qaView, presentQuestion());
    ASSERT_EQ(1, teacher->questionsToLearnNum());
    EXPECT_NO_THROW(teacher->showNextQuestion());
    ASSERT_EQ(0, teacher->questionsToLearnNum());
}

TEST_F(TeacherTestSuite, QAsToLearnProviderReturnOne_ShouldPresentQuestionAndThrowWhilePresentNext)
{
    QQueue<std::shared_ptr<QAView>> qas;
    auto qaView  = std::make_shared<StrictMock<QAViewMock>>();
    qas.push_back(qaView);
    EXPECT_CALL(*m_qasProvider, getQAs()).WillOnce(Return(qas));
    teacher = std::make_shared<Teacher>(m_qasProvider);

    EXPECT_CALL(*qaView, presentQuestion());
    ASSERT_EQ(1, teacher->questionsToLearnNum());
    EXPECT_NO_THROW(teacher->showNextQuestion());
    ASSERT_EQ(0, teacher->questionsToLearnNum());
    EXPECT_THROW(teacher->showNextQuestion(), std::logic_error);
}

TEST_F(TeacherTestSuite, QAsToLearnProviderReturnOne_ShouldPresentTwoQuestionAndMarkAsKnown)
{
    QQueue<std::shared_ptr<QAView>> qas;
    auto qaView1  = std::make_shared<StrictMock<QAViewMock>>();
    auto qaView2  = std::make_shared<StrictMock<QAViewMock>>();
    qas.push_back(qaView1);
    qas.push_back(qaView2);
    EXPECT_CALL(*m_qasProvider, getQAs()).WillOnce(Return(qas));
    teacher = std::make_shared<Teacher>(m_qasProvider);

    EXPECT_CALL(*qaView1, presentQuestion());
    ASSERT_EQ(2, teacher->questionsToLearnNum());
    EXPECT_NO_THROW(teacher->showNextQuestion());
    ASSERT_EQ(1, teacher->questionsToLearnNum());

    EXPECT_CALL(*qaView1, markAsKnown());
    teacher->markAsKnown();


    EXPECT_CALL(*qaView2, presentQuestion());
    ASSERT_EQ(1, teacher->questionsToLearnNum());
    EXPECT_NO_THROW(teacher->showNextQuestion());
    ASSERT_EQ(0, teacher->questionsToLearnNum());
}

TEST_F(TeacherTestSuite, QAsToLearnProviderReturnOne_ShouldPresentTwoQuestionAndMarkTwoAsUnknown)
{
    QQueue<std::shared_ptr<QAView>> qas;
    auto qaView1  = std::make_shared<StrictMock<QAViewMock>>();
    auto qaView2  = std::make_shared<StrictMock<QAViewMock>>();

    qas.push_back(qaView1);
    qas.push_back(qaView2);
    EXPECT_CALL(*m_qasProvider, getQAs()).WillOnce(Return(qas));
    teacher = std::make_shared<Teacher>(m_qasProvider);

    EXPECT_CALL(*qaView1, presentQuestion());
    ASSERT_EQ(2, teacher->questionsToLearnNum());
    EXPECT_NO_THROW(teacher->showNextQuestion());
    ASSERT_EQ(1, teacher->questionsToLearnNum());

    EXPECT_CALL(*qaView1, markAsUnknown());
    teacher->markAsUnknown();

    EXPECT_CALL(*qaView2, presentQuestion());
    ASSERT_EQ(2, teacher->questionsToLearnNum());
    EXPECT_NO_THROW(teacher->showNextQuestion());
    ASSERT_EQ(1, teacher->questionsToLearnNum());
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

