#include <memory>
#include "../gtest.h"
#include "../gmock.h"
#include "../../GonzalesApp/qa/qarepository.h"
#include "ExceptionHandlerMock.h"
#include "QuestionsCollectionPresenterMock.h"

using namespace testing;

TEST(QARepositoryTestSuite, noItemGivenShouldReturnNothing)
{
    std::shared_ptr<ExceptionHandlerMock> l_mock =  std::make_shared<ExceptionHandlerMock>();
    std::unique_ptr<QuestionCollectionPresenteMock> l_presenter(new QuestionCollectionPresenteMock);
    std::shared_ptr<IQARepository> repository = std::make_shared<QARepository>("BARTEK", l_mock, std::move(l_presenter));
    std::vector<QA> list;
    //repository->setQuestions(list);
    //EXPECT_TRUE(repository->getQAs().empty());
}

TEST(QARepositoryTestSuite, oneItemGivenShouldReturnOne)
{
//    std::shared_ptr<ExceptionHandlerMock> l_mock =  std::make_shared<ExceptionHandlerMock>();
//    std::unique_ptr<QuestionCollectionPresenteMock> l_presenter(new QuestionCollectionPresenteMock);

//    std::shared_ptr<IQARepository> repository = std::make_shared<QARepository>("BARTEK", l_mock, std::move(l_presenter));
//    std::vector<QA> list;
//    list.push_back(QA(Question("A"), Answer("N")));
//    //repository->setQuestions(list);
//    EXPECT_EQ(1, repository->getQAs().size());
}
