#include <memory>
#include "../gtest.h"
#include "../gmock.h"
#include "../../GonzalesApp/qa/QARepository.h"
#include "ExceptionHandlerMock.h"
#include "QuestionsCollectionPresenterMock.h"
#include "QALoaderMock.h"
#include "QASaverMock.h"

using namespace testing;

TEST(QARepositoryTestSuite, loadQAsWillThrow)
{
    std::shared_ptr<ExceptionHandlerMock> l_exceptionHandlerMock =  std::make_shared<ExceptionHandlerMock>();
    std::shared_ptr<QuestionCollectionPresenteMock> l_presenter = std::make_shared<QuestionCollectionPresenteMock>();
    std::shared_ptr<QALoaderMock> l_loaderMock = std::make_shared<QALoaderMock>();
    std::shared_ptr<QASaverMock> l_saverMock = std::make_shared<QASaverMock>();
    QString filePath = "filePath";
    EXPECT_CALL(*l_loaderMock, load()).WillOnce(Throw(FileException()));
    EXPECT_CALL(*l_exceptionHandlerMock, handleException(_,_));
    QARepository repository(filePath, l_exceptionHandlerMock, l_presenter, l_loaderMock, l_saverMock);
    EXPECT_NO_THROW(repository.load());
}

TEST(QARepositoryTestSuite, LoadQAsWillLoadQAProperly)
{
    std::shared_ptr<ExceptionHandlerMock> l_exceptionHandlerMock =  std::make_shared<ExceptionHandlerMock>();
    std::shared_ptr<QuestionCollectionPresenteMock> l_presenter = std::make_shared<QuestionCollectionPresenteMock>();
    std::shared_ptr<QALoaderMock> l_loaderMock = std::make_shared<QALoaderMock>();
    std::shared_ptr<QASaverMock> l_saverMock = std::make_shared<QASaverMock>();
    QString filePath = "filePath";
    SimpleTree::Node<QA> rootNode;
    EXPECT_CALL(*l_loaderMock, load()).WillOnce(Return(rootNode));
    EXPECT_CALL(*l_presenter, presentQuestions(rootNode));
    QARepository repository(filePath, l_exceptionHandlerMock, l_presenter, l_loaderMock, l_saverMock);
    EXPECT_NO_THROW(repository.load());
    EXPECT_EQ(rootNode, repository.getQAs());
}
