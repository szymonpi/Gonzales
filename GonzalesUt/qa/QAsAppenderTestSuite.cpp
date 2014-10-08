#include <memory>
#include "../gtest.h"
#include "../gmock.h"
#include "../../GonzalesApp/qa/qaio/QAsAppender.h"
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
    QAsAppender appender;
};

TEST_F(QAsAppenderTestSuite, shouldntAppendImportedQAsNoDestinationSelected)
{
    EXPECT_CALL(*destinationSelectorMock, select(_,_)).WillOnce(Return(false));
    SimpleTree::Node<QA> mainNode;
    EXPECT_CALL(*repositoryMock, getQAs()).WillOnce(ReturnRef(mainNode));
    appender.append(std::vector<std::shared_ptr<QA> >());
}

TEST_F(QAsAppenderTestSuite, shouldAppendOneImportedQAToExistingGroup)
{
    SimpleTree::Node<QA> rootNode;
    SimpleTree::Node<QA> group;
    group.setName("group");
    SimpleTree::Node<QA> subject;
    subject.setName("subject");
    subject.appendNode(group);
    rootNode.appendNode(subject);

    std::vector<std::shared_ptr<QA> > importedNodes;
    importedNodes.push_back(std::make_shared<QA>("question", "answer"));

    QMap<QString, QStringList> groupMap;
    groupMap["subject"] = QStringList() << "group";

    EXPECT_CALL(*repositoryMock, getQAs()).WillOnce(ReturnRef(rootNode));
    EXPECT_CALL(*destinationSelectorMock, select(groupMap, QStringList() << "question")).WillOnce(Return(true));
    EXPECT_CALL(*destinationSelectorMock, getSubject()).WillOnce(Return("subject"));
    EXPECT_CALL(*destinationSelectorMock, getGroup()).WillOnce(Return("group"));
    EXPECT_CALL(*repositoryMock, onQAsImport());
    appender.append(importedNodes);
    ASSERT_GT(rootNode.size(), 0);
    ASSERT_FALSE(rootNode.getNode(0).getNodes().empty());
    ASSERT_EQ(1, rootNode.getNode(0).getNodes().at(0).size());
    ASSERT_EQ(importedNodes.at(0), rootNode.getNode(0).getNodes().at(0).getNodes().at(0).getNodeValue());
}

TEST_F(QAsAppenderTestSuite, shouldAppendOneImportedQAToNotExistingGroup)
{
    SimpleTree::Node<QA> rootNode;
    SimpleTree::Node<QA> group;
    group.setName("group");
    SimpleTree::Node<QA> subject;
    subject.setName("subject");
    subject.appendNode(group);
    rootNode.appendNode(subject);

    std::vector<std::shared_ptr<QA> > importedNodes;
    importedNodes.push_back(std::make_shared<QA>("question", "answer"));

    QMap<QString, QStringList> groupMap;
    groupMap["subject"] = QStringList() << "group";

    EXPECT_CALL(*repositoryMock, getQAs()).WillOnce(ReturnRef(rootNode));
    EXPECT_CALL(*destinationSelectorMock, select(groupMap, QStringList() << "question")).WillOnce(Return(true));
    EXPECT_CALL(*destinationSelectorMock, getSubject()).WillOnce(Return("subject"));
    EXPECT_CALL(*destinationSelectorMock, getGroup()).WillOnce(Return("different_group"));
    EXPECT_CALL(*repositoryMock, onQAsImport());
    appender.append(importedNodes);
    ASSERT_GT(rootNode.size(), 0);
    ASSERT_FALSE(rootNode.getNode(0).getNodes().empty());
                //subjects ------groups---first group size
    ASSERT_EQ(1, rootNode.getNode(0).getNodes().at(1).size());
                                   //subjects ------groups---newly imported nodes first new QA Value
    ASSERT_EQ(importedNodes.at(0), rootNode.getNode(0).getNodes().at(1).getNodes().at(0).getNodeValue());
}

TEST_F(QAsAppenderTestSuite, shouldAppendOneImportedQAToNotExistingSubjectAndGroup)
{
    SimpleTree::Node<QA> rootNode;
    SimpleTree::Node<QA> group;
    group.setName("group");
    SimpleTree::Node<QA> subject;
    subject.setName("subject");
    subject.appendNode(group);
    rootNode.appendNode(subject);

    std::vector<std::shared_ptr<QA> > importedQAs;
    importedQAs.push_back(std::make_shared<QA>("question", "answer"));

    QMap<QString, QStringList> groupMap;
    groupMap["subject"] = QStringList() << "group";

    EXPECT_CALL(*repositoryMock, getQAs()).WillOnce(ReturnRef(rootNode));
    EXPECT_CALL(*destinationSelectorMock, select(groupMap, QStringList() << "question")).WillOnce(Return(true));
    EXPECT_CALL(*destinationSelectorMock, getSubject()).WillOnce(Return("different_subject"));
    EXPECT_CALL(*destinationSelectorMock, getGroup()).WillOnce(Return("different_group"));
    EXPECT_CALL(*repositoryMock, onQAsImport());
    appender.append(importedQAs);
    ASSERT_GT(rootNode.size(), 0);
    ASSERT_FALSE(rootNode.getNode(1).getNodes().empty());
                //subjects ------groups---first group size
    ASSERT_EQ(1, rootNode.getNode(1).getNodes().at(0).size());
                                   //subjects ------groups---newly imported nodes first new QA Value
    ASSERT_EQ(importedQAs.at(0), rootNode.getNode(1).getNodes().at(0).getNodes().at(0).getNodeValue());
}
