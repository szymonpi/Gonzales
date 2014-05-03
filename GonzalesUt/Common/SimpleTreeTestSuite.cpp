#include "../gtest.h"
#include "../gmock.h"
#include "../../GonzalesApp/common/SimpleTree/node.h"
#include "../AQImporter/FileDeserializerMock.h"
#include "../AQImporter/FileSerializerMock.h"
#include <QString>

using namespace testing;
using namespace SimpleTree;

TEST(SimpleTreeTestSuite, createRootItem)
{
    Node<int> node;
    EXPECT_FALSE(node.getNodeValue().get());
    EXPECT_EQ(0, node.size());
}

TEST(SimpleTreeTestSuite, GivenRootItemAnd2NodesInIt_ShouldReturnProperNodeValues)
{
    Node<int> node;
    node.emplaceNode(std::make_shared<int>(3));
    node.emplaceNode(std::make_shared<int>(5));

    EXPECT_EQ(2, node.size());
    EXPECT_EQ(3, *node.getNode(0).getNodeValue());
    EXPECT_EQ(5, *node.getNode(1).getNodeValue());
}

TEST(SimpleTreeTestSuite, GivenRootItemAnd5NodesInIt4NodeRemoved_ShouldReturnProperNodeValues)
{
    Node<int> node;
    node.emplaceNode(std::make_shared<int>(1));
    node.emplaceNode(std::make_shared<int>(2));
    node.emplaceNode(std::make_shared<int>(3));
    node.emplaceNode(std::make_shared<int>(4));
    node.emplaceNode(std::make_shared<int>(5));
    node.removeNode(2);

    EXPECT_EQ(1, *node.getNode(0).getNodeValue());
    EXPECT_EQ(2, *node.getNode(1).getNodeValue());
    EXPECT_EQ(4, *node.getNode(2).getNodeValue());
    EXPECT_EQ(5, *node.getNode(3).getNodeValue());
}

TEST(SimpleTreeTestSuite, GivenRootItemAnd5NodesInIt5thNodeHas3Nodes_ShouldReturnProperNodeValues)
{
    Node<int> node;
    node.emplaceNode(std::make_shared<int>(1));
    node.emplaceNode(std::make_shared<int>(2));
    node.emplaceNode(std::make_shared<int>(3));
    node.emplaceNode(std::make_shared<int>(4));
    node.emplaceNode(std::make_shared<int>(5));

    node.getNode(4).emplaceNode(std::make_shared<int>(6));
    node.getNode(4).emplaceNode(std::make_shared<int>(7));
    node.getNode(4).emplaceNode(std::make_shared<int>(8));

    EXPECT_EQ(1, *node.getNode(0).getNodeValue());
    EXPECT_EQ(2, *node.getNode(1).getNodeValue());
    EXPECT_EQ(3, *node.getNode(2).getNodeValue());
    EXPECT_EQ(4, *node.getNode(3).getNodeValue());
    EXPECT_EQ(5, *node.getNode(4).getNodeValue());

    EXPECT_EQ(6, *node.getNode(4).getNode(0).getNodeValue());
    EXPECT_EQ(7, *node.getNode(4).getNode(1).getNodeValue());
    EXPECT_EQ(8, *node.getNode(4).getNode(2).getNodeValue());
}



