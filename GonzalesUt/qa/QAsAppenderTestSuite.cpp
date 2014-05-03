#include <memory>
#include "../gtest.h"
#include "../gmock.h"
#include "../../GonzalesApp/qa/importedqasappender.h"
#include "QAsDestinationSelectorMock.h"
#include "QAsRepositoryMock.h"

using namespace testing;

class QAsAppenderTestSuite: public testing::Test
{
protected:
    QAsAppenderTestSuite():
        destinationSelectorMock(std::make_shared<QAsDestinationSelectorMock>()),
        repositoryMock(std::make_shared<QAsRepositoryMock>()),
        appender(destinationSelectorMock, repositoryMock)
    {}

    std::shared_ptr<QAsDestinationSelectorMock> destinationSelectorMock;
    std::shared_ptr<QAsRepositoryMock> repositoryMock;
    ImportedQAsAppender appender;
};

TEST_F(QAsAppenderTestSuite, shouldntAppendImportedQAsNoDestinationSelected)
{
    EXPECT_CALL(*destinationSelectorMock, select(_,_)).WillOnce(Return(false));
    std::vector<SimpleTree::Node<QA> > allNodes;
    EXPECT_CALL(*repositoryMock, getQAs()).WillOnce(ReturnRef(allNodes));
    appender.append(std::vector<std::shared_ptr<QA> >());
}

TEST_F(QAsAppenderTestSuite, shouldAppendOneImportedQAToExistingGroup)
{
    std::vector<SimpleTree::Node<QA> > allNodes;
    SimpleTree::Node<QA> group;
    group.setName("group");
    SimpleTree::Node<QA> subject;
    subject.setName("subject");
    subject.appendNode(group);
    allNodes.push_back(subject);

    std::vector<std::shared_ptr<QA> > importedNodes;
    importedNodes.push_back(std::make_shared<QA>(Question("question"), Answer("answer")));

    QMap<QString, QStringList> groupMap;
    groupMap["subject"] = QStringList() << "group";

    EXPECT_CALL(*repositoryMock, getQAs()).WillOnce(ReturnRef(allNodes));
    EXPECT_CALL(*destinationSelectorMock, select(groupMap, QStringList() << "question")).WillOnce(Return(true));
    EXPECT_CALL(*destinationSelectorMock, getSubject()).WillOnce(Return("subject"));
    EXPECT_CALL(*destinationSelectorMock, getGroup()).WillOnce(Return("group"));
    appender.append(importedNodes);
    ASSERT_FALSE(allNodes.empty());
    ASSERT_FALSE(allNodes.at(0).getNodes().empty());
    ASSERT_EQ(1, allNodes.at(0).getNodes().at(0).size());
    ASSERT_EQ(importedNodes.at(0), allNodes.at(0).getNodes().at(0).getNodes().at(0).getNodeValue());
}

TEST_F(QAsAppenderTestSuite, shouldAppendOneImportedQAToNotExistingGroup)
{
    std::vector<SimpleTree::Node<QA> > allNodes;
    SimpleTree::Node<QA> group;
    group.setName("group");
    SimpleTree::Node<QA> subject;
    subject.setName("subject");
    subject.appendNode(group);
    allNodes.push_back(subject);

    std::vector<std::shared_ptr<QA> > importedNodes;
    importedNodes.push_back(std::make_shared<QA>(Question("question"), Answer("answer")));

    QMap<QString, QStringList> groupMap;
    groupMap["subject"] = QStringList() << "group";

    EXPECT_CALL(*repositoryMock, getQAs()).WillOnce(ReturnRef(allNodes));
    EXPECT_CALL(*destinationSelectorMock, select(groupMap, QStringList() << "question")).WillOnce(Return(true));
    EXPECT_CALL(*destinationSelectorMock, getSubject()).WillOnce(Return("subject"));
    EXPECT_CALL(*destinationSelectorMock, getGroup()).WillOnce(Return("different_group"));
    appender.append(importedNodes);
    ASSERT_FALSE(allNodes.empty());
    ASSERT_FALSE(allNodes.at(0).getNodes().empty());
                //subjects ------groups---first group size
    ASSERT_EQ(1, allNodes.at(0).getNodes().at(1).size());
                                   //subjects ------groups---newly imported nodes first new QA Value
    ASSERT_EQ(importedNodes.at(0), allNodes.at(0).getNodes().at(1).getNodes().at(0).getNodeValue());
}

TEST_F(QAsAppenderTestSuite, shouldAppendOneImportedQAToNotExistingSubjectAndGroup)
{
    std::vector<SimpleTree::Node<QA> > allNodes;
    SimpleTree::Node<QA> group;
    group.setName("group");
    SimpleTree::Node<QA> subject;
    subject.setName("subject");
    subject.appendNode(group);
    allNodes.push_back(subject);

    std::vector<std::shared_ptr<QA> > importedNodes;
    importedNodes.push_back(std::make_shared<QA>(Question("question"), Answer("answer")));

    QMap<QString, QStringList> groupMap;
    groupMap["subject"] = QStringList() << "group";

    EXPECT_CALL(*repositoryMock, getQAs()).WillOnce(ReturnRef(allNodes));
    EXPECT_CALL(*destinationSelectorMock, select(groupMap, QStringList() << "question")).WillOnce(Return(true));
    EXPECT_CALL(*destinationSelectorMock, getSubject()).WillOnce(Return("different_subject"));
    EXPECT_CALL(*destinationSelectorMock, getGroup()).WillOnce(Return("different_group"));
    appender.append(importedNodes);
    ASSERT_FALSE(allNodes.empty());
    ASSERT_FALSE(allNodes.at(1).getNodes().empty());
                //subjects ------groups---first group size
    ASSERT_EQ(1, allNodes.at(1).getNodes().at(0).size());
                                   //subjects ------groups---newly imported nodes first new QA Value
    ASSERT_EQ(importedNodes.at(0), allNodes.at(1).getNodes().at(0).getNodes().at(0).getNodeValue());
}
