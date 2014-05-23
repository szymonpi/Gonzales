
#include <memory>
#include "../gtest.h"
#include "../gmock.h"
#include "../../GonzalesApp/qa/QAsToLearnSelector.h"
#include "../../GonzalesApp/common/SimpleTree/Node.h"
#include "QAsProviderMock.h"

using namespace testing;

class QAsToLearnSelectorTestSuite: public testing::Test
{
protected:
    QAsToLearnSelectorTestSuite():
        qAsProvider(std::make_shared<QAsProviderMock>()),
        checker(qAsProvider)
    {
        subject.setText(0, "subject");
        group.setText(0, "group");
        group.addChild(&qA);
        subject.addChild(&group);


    }
    std::shared_ptr<QAsProviderMock> qAsProvider;
    QAsToLearnSelector checker;
    QTreeWidgetItem emptyItem;
    QTreeWidgetItem subject;
    QTreeWidgetItem group;
    QTreeWidgetItem qA;

};

TEST_F(QAsToLearnSelectorTestSuite, emptyItemGivenShouldSelectNothing)
{
    checker.select(emptyItem);
}

TEST_F(QAsToLearnSelectorTestSuite, groupItemGivenShouldSelectOneQA)
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

    EXPECT_CALL(*qAsProvider, getQAs()).WillOnce(ReturnRef(rootNode));
    std::shared_ptr<QA> qa = rootNode.getNodes().at(0).getNodes().at(0).getNodes().at(0).getNodeValue();
    checker.select(group);
    ASSERT_EQ(true, qa->m_toLearn);
}

TEST_F(QAsToLearnSelectorTestSuite, wrongSubjectNameGivenShouldThrow)
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

    QTreeWidgetItem group1;
    QTreeWidgetItem wrongSubjectName;
    wrongSubjectName.setText(0, "unsupported");
    wrongSubjectName.addChild(&group1);

    EXPECT_CALL(*qAsProvider, getQAs()).WillOnce(ReturnRef(rootNode));
    EXPECT_THROW(checker.select(wrongSubjectName), std::logic_error);
    int i = 5;
    i = i*i;
}

TEST_F(QAsToLearnSelectorTestSuite, subjectItemGivenShouldSelectOneQA)
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

    EXPECT_CALL(*qAsProvider, getQAs()).WillOnce(ReturnRef(rootNode));
    std::shared_ptr<QA> qa = rootNode.getNodes().at(0).getNodes().at(0).getNodes().at(0).getNodeValue();
    checker.select(subject);
    ASSERT_EQ(true, qa->m_toLearn);
}


