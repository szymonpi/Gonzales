
#include "../gtest.h"
#include "../gmock.h"
#include "../../GonzalesApp/common/simpletree.h"
#include "../AQImporter/FileDeserializerMock.h"
#include "../CommonUtUtilities/CommonMocks.h"
//#include "../CommonUtUtilities/PrintTo.h"
#include <QString>

using namespace testing;

class DeserializationTestSuite: public testing::Test
{
public:
    DeserializationTestSuite()
    {
    }
    FileDeserializerMock deserializerMock;
    std::shared_ptr<NodeValueStub> value = std::make_shared<NodeValueStub>();
    quint8 nodeTypeEmpty = SimpleTree::NodeType_Empty;
    quint8 nodeTypeWithValue = SimpleTree::NodeType_WithValue;
    quint8 nodeTypeWithChildren = SimpleTree::NodeType_WithChildren;

};

//___
//| |
//---

TEST_F(DeserializationTestSuite, DeserializeOneEmptyNode)
{
    Node<NodeValueStub> node;

    EXPECT_CALL(deserializerMock, deserialize(An<quint8 &>())).WillOnce(SetArgReferee<0>(nodeTypeEmpty));
    EXPECT_THROW(SimpleTree::deserialize(deserializerMock, node), std::logic_error);
}

//___
//|o|
//---

TEST_F(DeserializationTestSuite, DeserializeOneNodeWithValue)
{
    Node<NodeValueStub> node;

    unsigned numOfChildren = 0;

    EXPECT_CALL(deserializerMock, deserialize(An<quint8 &>())).WillOnce(SetArgReferee<0>(nodeTypeWithValue));
    EXPECT_CALL(deserializerMock, deserialize(An<unsigned &>())).WillOnce(SetArgReferee<0>(numOfChildren));

    SimpleTree::deserialize(deserializerMock, node);

    ASSERT_TRUE(node.getNodeValue().get());
}

//___
//| |
//---
//   \___
//    |o|
//    ---

TEST_F(DeserializationTestSuite, DeserializeOneNodeWithOneChild)
{
    Node<NodeValueStub> nodeWithChildren;

    unsigned numOfChildrenNodeWithChild = 1;
    unsigned numOfChildren = 0;

    QString mainNodeName = "mainNode";

    EXPECT_CALL(deserializerMock, deserialize(An<quint8 &>()))
        .WillOnce(SetArgReferee<0>(nodeTypeWithChildren))
        .WillOnce(SetArgReferee<0>(nodeTypeWithValue));

    EXPECT_CALL(deserializerMock, deserialize(An<unsigned &>()))
            .WillOnce(SetArgReferee<0>(numOfChildrenNodeWithChild))
            .WillOnce(SetArgReferee<0>(numOfChildren));

    EXPECT_CALL(deserializerMock, deserialize(An<QString &>())).WillOnce(SetArgReferee<0>(mainNodeName));

    SimpleTree::deserialize(deserializerMock, nodeWithChildren);

    EXPECT_EQ(mainNodeName, nodeWithChildren.getName());
    ASSERT_EQ(1, nodeWithChildren.size());
    ASSERT_TRUE(nodeWithChildren.getNode(0).getNodeValue().get());
}

//___
//| |
//---
//   \___ ___ ___
//    |o| |o| |o|
//    --- --- ---

TEST_F(DeserializationTestSuite, DeserializeOneNodeWithThreeChild)
{
    Node<NodeValueStub> nodeWithChildren;

    unsigned numOfChildrenNodeWithChild = 3;
    unsigned numOfChildren = 0;

    QString mainNodeName = "mainNode";

    EXPECT_CALL(deserializerMock, deserialize(An<quint8 &>()))
        .WillOnce(SetArgReferee<0>(nodeTypeWithChildren))
        .WillOnce(SetArgReferee<0>(nodeTypeWithValue))
        .WillOnce(SetArgReferee<0>(nodeTypeWithValue))
        .WillOnce(SetArgReferee<0>(nodeTypeWithValue));

    EXPECT_CALL(deserializerMock, deserialize(An<unsigned &>()))
            .WillOnce(SetArgReferee<0>(numOfChildrenNodeWithChild))
            .WillOnce(SetArgReferee<0>(numOfChildren))
            .WillOnce(SetArgReferee<0>(numOfChildren))
            .WillOnce(SetArgReferee<0>(numOfChildren));

    EXPECT_CALL(deserializerMock, deserialize(An<QString &>())).WillOnce(SetArgReferee<0>(mainNodeName));

    SimpleTree::deserialize(deserializerMock, nodeWithChildren);

    EXPECT_EQ(mainNodeName, nodeWithChildren.getName());
    ASSERT_EQ(3, nodeWithChildren.size());
    ASSERT_TRUE(nodeWithChildren.getNode(0).getNodeValue().get());
    ASSERT_TRUE(nodeWithChildren.getNode(1).getNodeValue().get());
    ASSERT_TRUE(nodeWithChildren.getNode(2).getNodeValue().get());
}

//___
//| |
//--- ----------------
//   \___             \___
//    | |              | |
//    ---              ---
//       \___ ___ ___     \___ ___ ___
//        |o| |o| |o|      |o| |o| |o|
//        --- --- ---      --- --- ---

TEST_F(DeserializationTestSuite, DeserializeOneNodeWithTwoChildrenWithThreeNodeInEach)
{
    Node<NodeValueStub> nodeWithChildren;

    unsigned numOfChildrenNodeWithChild3 = 3;
    unsigned numOfChildrenNodeWithChild2 = 2;
    unsigned numOfChildren = 0;

    QString mainNodeName = "mainNode";
    QString nodeFirstWithChildrenName = "firstNodeWithChildren";
    QString nodeSecondWithChildrenName = "secondNodeWithChildren";

    EXPECT_CALL(deserializerMock, deserialize(An<quint8 &>()))
        .WillOnce(SetArgReferee<0>(nodeTypeWithChildren))
        .WillOnce(SetArgReferee<0>(nodeTypeWithChildren))
        .WillOnce(SetArgReferee<0>(nodeTypeWithValue))
        .WillOnce(SetArgReferee<0>(nodeTypeWithValue))
        .WillOnce(SetArgReferee<0>(nodeTypeWithValue))
        .WillOnce(SetArgReferee<0>(nodeTypeWithChildren))
        .WillOnce(SetArgReferee<0>(nodeTypeWithValue))
        .WillOnce(SetArgReferee<0>(nodeTypeWithValue))
        .WillOnce(SetArgReferee<0>(nodeTypeWithValue));

    EXPECT_CALL(deserializerMock, deserialize(An<unsigned &>()))
        .WillOnce(SetArgReferee<0>(numOfChildrenNodeWithChild2))
        .WillOnce(SetArgReferee<0>(numOfChildrenNodeWithChild3))
        .WillOnce(SetArgReferee<0>(numOfChildren))
        .WillOnce(SetArgReferee<0>(numOfChildren))
        .WillOnce(SetArgReferee<0>(numOfChildren))
        .WillOnce(SetArgReferee<0>(numOfChildrenNodeWithChild3))
        .WillOnce(SetArgReferee<0>(numOfChildren))
        .WillOnce(SetArgReferee<0>(numOfChildren))
        .WillOnce(SetArgReferee<0>(numOfChildren));

    EXPECT_CALL(deserializerMock, deserialize(An<QString &>()))
            .WillOnce(SetArgReferee<0>(mainNodeName))
            .WillOnce(SetArgReferee<0>(nodeFirstWithChildrenName))
            .WillOnce(SetArgReferee<0>(nodeSecondWithChildrenName));

    SimpleTree::deserialize(deserializerMock, nodeWithChildren);

    EXPECT_EQ(mainNodeName, nodeWithChildren.getName());
    EXPECT_EQ(nodeFirstWithChildrenName, nodeWithChildren.getNode(0).getName());
    EXPECT_EQ(nodeSecondWithChildrenName, nodeWithChildren.getNode(1).getName());
    ASSERT_EQ(2, nodeWithChildren.size());
    ASSERT_EQ(3, nodeWithChildren.getNode(0).size());
    ASSERT_EQ(3, nodeWithChildren.getNode(1).size());
    ASSERT_TRUE(nodeWithChildren.getNode(0).getNode(0).getNodeValue().get());
    ASSERT_TRUE(nodeWithChildren.getNode(0).getNode(1).getNodeValue().get());
    ASSERT_TRUE(nodeWithChildren.getNode(0).getNode(2).getNodeValue().get());

    ASSERT_TRUE(nodeWithChildren.getNode(1).getNode(0).getNodeValue().get());
    ASSERT_TRUE(nodeWithChildren.getNode(1).getNode(1).getNodeValue().get());
    ASSERT_TRUE(nodeWithChildren.getNode(1).getNode(2).getNodeValue().get());
}



