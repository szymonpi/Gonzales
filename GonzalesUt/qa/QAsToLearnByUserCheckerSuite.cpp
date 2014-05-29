
#include <memory>
#include "../gtest.h"
#include "../gmock.h"
#include "../../GonzalesApp/qa/QAsSelection/QAsToLearnByUserChecker.h"
#include "../../GonzalesApp/common/SimpleTree/Node.h"
#include "QAsRepositoryMock.h"
#include "../../GonzalesApp/common/Common.h"

using namespace testing;

class QAsToLearnByUserSelector: public testing::Test
{
protected:
    QAsToLearnByUserSelector():
        qAsRepositoryMock(std::make_shared<QAsRepositoryMock>()),
        checker(qAsRepositoryMock)
    {
        subject.setText(0, "subject");
        group.setText(0, "group");
        group.addChild(&qA);
        subject.addChild(&group);


    }
    std::shared_ptr<QAsRepositoryMock> qAsRepositoryMock;
    QAsToLearnByUserChecker checker;
    QTreeWidgetItem emptyItem;
    QTreeWidgetItem subject;
    QTreeWidgetItem group;
    QTreeWidgetItem qA;

};

TEST_F(QAsToLearnByUserSelector, emptyItemGivenShouldSelectNothing)
{
    checker.select(emptyItem);
}

TEST_F(QAsToLearnByUserSelector, groupItemGivenShouldSelectOneGroup)
{
    //qas
    SimpleTree::Node<QA> rootNode;
    SimpleTree::Node<QA> subjectNode;
    subjectNode.setName("subject");

    SimpleTree::Node<QA> groupNode;
    groupNode.setName("group");

    group.setCheckState(2, Qt::Checked);

    groupNode.emplaceNode(std::make_shared<QA>(Question("question"), Answer("anser")));
    subjectNode.appendNode(groupNode);
    rootNode.appendNode(subjectNode);

    EXPECT_CALL(*qAsRepositoryMock, onQAsUpdate());
    EXPECT_CALL(*qAsRepositoryMock, getQAs()).WillOnce(ReturnPointee(&rootNode));
    checker.select(group);
    auto subjectNodeSet = rootNode.getNodes().at(0);
    auto groupNodeSet = rootNode.getNodes().at(0).getNodes().at(0);
    ASSERT_EQ(false, subjectNodeSet.getInfo(NODE_INFO_ROLE_CHECKED).toBool());
    ASSERT_EQ(true, groupNodeSet.getInfo(NODE_INFO_ROLE_CHECKED).toBool());
    ASSERT_EQ(true, groupNodeSet.getNodes().at(0).getInfo(NODE_INFO_ROLE_CHECKED));
}

TEST_F(QAsToLearnByUserSelector, wrongSubjectNameGivenShouldThrow)
{
    //qas
    SimpleTree::Node<QA> rootNode;
    SimpleTree::Node<QA> subjectNode;
    subjectNode.setName("subject");

    SimpleTree::Node<QA> groupNode;
    groupNode.setName("group");

    groupNode.emplaceNode(std::make_shared<QA>(Question("question"), Answer("anser")));
    subjectNode.appendNode(groupNode);
    rootNode.appendNode(subjectNode);

    subject.setText(0, "unsupported");

    EXPECT_CALL(*qAsRepositoryMock, getQAs()).WillOnce(ReturnRef(rootNode));
    EXPECT_THROW(checker.select(subject), std::logic_error);
}

TEST_F(QAsToLearnByUserSelector, wrongGroupNameGivenShouldThrow)
{
    //qas
    SimpleTree::Node<QA> rootNode;
    SimpleTree::Node<QA> subjectNode;
    subjectNode.setName("subject");

    SimpleTree::Node<QA> groupNode;
    groupNode.setName("group");

    groupNode.emplaceNode(std::make_shared<QA>(Question("question"), Answer("anser")));
    subjectNode.appendNode(groupNode);
    rootNode.appendNode(subjectNode);

    group.setText(0, "unsupported");

    EXPECT_CALL(*qAsRepositoryMock, getQAs()).WillOnce(ReturnRef(rootNode));
    EXPECT_THROW(checker.select(group), std::logic_error);
}

TEST_F(QAsToLearnByUserSelector, subjectItemGivenShouldSelectGroups)
{
    //qas
    SimpleTree::Node<QA> rootNode;
    SimpleTree::Node<QA> subjectNode;
    subjectNode.setName("subject");

    SimpleTree::Node<QA> groupNode;
    groupNode.setName("group");

    group.setCheckState(2, Qt::Checked);
    subject.setCheckState(2, Qt::Checked);

    groupNode.emplaceNode(std::make_shared<QA>(Question("question"), Answer("anser")));
    subjectNode.appendNode(groupNode);
    rootNode.appendNode(subjectNode);

    EXPECT_CALL(*qAsRepositoryMock, onQAsUpdate());
    EXPECT_CALL(*qAsRepositoryMock, getQAs()).WillOnce(ReturnRef(rootNode));
    checker.select(subject);

    auto subjectNodeSet = rootNode.getNodes().at(0);
    auto groupNodeSet = rootNode.getNodes().at(0).getNodes().at(0);
    ASSERT_EQ(true, subjectNodeSet.getInfo(NODE_INFO_ROLE_CHECKED));
    ASSERT_EQ(true, groupNodeSet.getInfo(NODE_INFO_ROLE_CHECKED));
    ASSERT_EQ(true, groupNodeSet.getNodes().at(0).getInfo(NODE_INFO_ROLE_CHECKED));
}


