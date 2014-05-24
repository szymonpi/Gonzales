#include <memory>
#include "../gtest.h"
#include "../gmock.h"
#include "../../GonzalesApp/qa/QAsToLearnProvider.h"
#include "../../GonzalesApp/common/SimpleTree/Node.h"
#include "QAsProviderMock.h"
#include "../../GonzalesApp/common/Common.h"

using namespace testing;

class QAsToLearnProvidertestSuite: public testing::Test
{
protected:
    QAsToLearnProvidertestSuite():
        m_qasProvider(std::make_shared<QAsProviderMock>()),
        m_qasToLearnProvider(m_qasProvider)
    {

    }
    std::shared_ptr<QAsProviderMock> m_qasProvider;
    QAsToLearnProvider m_qasToLearnProvider;
    std::shared_ptr<QA> m_qa = std::make_shared<QA>(Question("question"), Answer("answer"));
};

TEST_F(QAsToLearnProvidertestSuite, NoQAsGivenFromQARepositoryInRootNode_ShouldThrow)
{
    SimpleTree::Node<QA> node;
    EXPECT_CALL(*m_qasProvider, getQAs()).WillOnce(ReturnRef(node));
    EXPECT_THROW(m_qasToLearnProvider.getQAs(), std::logic_error);
}

TEST_F(QAsToLearnProvidertestSuite, OneQANodeWithQAGivenFromQARepositoryInRootNode_ShouldntProvideOneQABecauseWasNotSetToLearn)
{
    SimpleTree::Node<QA> node(m_qa);
    node.setInfo(NODE_INFO_ROLE_CHECKED, false);
    EXPECT_CALL(*m_qasProvider, getQAs()).WillOnce(ReturnRef(node));
    QQueue<std::shared_ptr<QA>> qas = m_qasToLearnProvider.getQAs();
    EXPECT_EQ(0, qas.size());
}

TEST_F(QAsToLearnProvidertestSuite, OneQANodeWithQAGivenFromQARepositoryInRootNode_ShouldntProvideOneQABecauseNodeIsEmpty)
{
    SimpleTree::Node<QA> node;
    EXPECT_CALL(*m_qasProvider, getQAs()).WillOnce(ReturnRef(node));
    EXPECT_THROW(m_qasToLearnProvider.getQAs(), std::logic_error);
}

TEST_F(QAsToLearnProvidertestSuite, OneQANodeWithQAGivenFromQARepositoryInRootNode_ShouldProvideOneQA)
{
    SimpleTree::Node<QA> node(m_qa);
    node.setInfo(NODE_INFO_ROLE_CHECKED, true);
    EXPECT_CALL(*m_qasProvider, getQAs()).WillOnce(ReturnRef(node));
    QQueue<std::shared_ptr<QA>> qas = m_qasToLearnProvider.getQAs();
    EXPECT_EQ(1, qas.size());
}

TEST_F(QAsToLearnProvidertestSuite, ThreeQANodeWithQAGivenFromQARepositoryInRootNode_ShouldProvideThreeQA)
{
    SimpleTree::Node<QA> rootNode;

    SimpleTree::Node<QA> node1(m_qa);
    SimpleTree::Node<QA> node2(m_qa);
    SimpleTree::Node<QA> node3(m_qa);

    node1.setInfo(NODE_INFO_ROLE_CHECKED, true);
    node2.setInfo(NODE_INFO_ROLE_CHECKED, true);
    node3.setInfo(NODE_INFO_ROLE_CHECKED, true);

    rootNode.appendNode(node1);
    rootNode.appendNode(node2);
    rootNode.appendNode(node3);

    EXPECT_CALL(*m_qasProvider, getQAs()).WillOnce(ReturnRef(rootNode));
    QQueue<std::shared_ptr<QA>> qas = m_qasToLearnProvider.getQAs();
    EXPECT_EQ(3, qas.size());
}


