
#include "../gtest.h"
#include "../gmock.h"
#include "../../GonzalesApp/common/SimpleTree/NodeSerializer.h"
#include "../AQImporter/DataDeserializerMock.h"
#include "../CommonUtUtilities/CommonMocks.h"
#include "../CommonUtUtilities/PrintTo.h"
#include "../../GonzalesApp/common/Common.h"
#include "InfosDeserializerMock.h"
#include <QString>

using namespace testing;
using namespace SimpleTree;
using namespace SimpleTree::Utils;

class DeserializationTestSuite: public testing::Test
{
public:
    DeserializationTestSuite():
        serializer(infosDeserializer)
    {
    }
    DataDeserializerMock deserializerMock;
    std::shared_ptr<StrictMock<InfosSerializerMock>> infosDeserializer = std::make_shared<StrictMock<InfosSerializerMock>>();
    std::shared_ptr<NodeValueStub> value = std::make_shared<NodeValueStub>();
    quint8 m_nodeType_Empty = NodeType_Empty;
    quint8 m_nodeType_WithValue = NodeType_WithValue;
    quint8 m_nodeType_WithChildren = NodeType_WithChildren;
    QMap<quint8, QVariant> m_infos;
    unsigned numOfChildren_0 = 0;
    NodeSerializer serializer;

};

//___
//| |
//---

TEST_F(DeserializationTestSuite, DeserializeOneEmptyNode)
{
    Node<NodeValueStub> node;

    EXPECT_CALL(deserializerMock, deserialize(An<quint8 &>())).WillOnce(SetArgReferee<0>(m_nodeType_Empty));
    EXPECT_THROW(serializer.deserialize(deserializerMock, node), std::logic_error);
}

//___
//|o|
//---

TEST_F(DeserializationTestSuite, DeserializeOneNodeWithValue)
{
    Node<NodeValueStub> node;

    EXPECT_CALL(deserializerMock, deserialize(An<quint8 &>())).WillOnce(SetArgReferee<0>(m_nodeType_WithValue));
    EXPECT_CALL(deserializerMock, deserialize(An<unsigned &>())).WillOnce(SetArgReferee<0>(numOfChildren_0));
    EXPECT_CALL(*infosDeserializer, deserialize(_,_)).WillOnce(SetArgReferee<1>(m_infos));

    serializer.deserialize(deserializerMock, node);

    ASSERT_TRUE(node.getNodeValue().get());
}

//___
//|o|
//--- *

TEST_F(DeserializationTestSuite, DeserializeOneNodeWithValueAndInfo)
{
    Node<NodeValueStub> node;

    EXPECT_CALL(deserializerMock, deserialize(An<quint8 &>())).WillOnce(SetArgReferee<0>(m_nodeType_WithValue));
    EXPECT_CALL(deserializerMock, deserialize(An<unsigned &>())).WillOnce(SetArgReferee<0>(numOfChildren_0));

    QMap<quint8, QVariant> infos;
    infos[NODE_INFO_ROLE_CHECKED] = true;
    EXPECT_CALL(*infosDeserializer, deserialize(_,_)).WillOnce(SetArgReferee<1>(infos));

    serializer.deserialize(deserializerMock, node);

    ASSERT_TRUE(node.getNodeValue().get());
    ASSERT_TRUE(node.getInfo(NODE_INFO_ROLE_CHECKED).toBool());
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

    QMap<quint8, QVariant> infos;
    EXPECT_CALL(*infosDeserializer, deserialize(_,_)).Times(2).WillRepeatedly(SetArgReferee<1>(infos));
    EXPECT_CALL(deserializerMock, deserialize(An<quint8 &>()))
        .WillOnce(SetArgReferee<0>(m_nodeType_WithChildren))
        .WillOnce(SetArgReferee<0>(m_nodeType_WithValue));

    EXPECT_CALL(deserializerMock, deserialize(An<unsigned &>()))
            .WillOnce(SetArgReferee<0>(numOfChildrenNodeWithChild))
            .WillOnce(SetArgReferee<0>(numOfChildren_0));

    EXPECT_CALL(deserializerMock, deserialize(An<QString &>())).WillOnce(SetArgReferee<0>(mainNodeName));

    serializer.deserialize(deserializerMock, nodeWithChildren);

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

    QMap<quint8, QVariant> infos;
    EXPECT_CALL(*infosDeserializer, deserialize(_,_)).Times(4).WillRepeatedly(SetArgReferee<1>(infos));
    EXPECT_CALL(deserializerMock, deserialize(An<quint8 &>()))
        .WillOnce(SetArgReferee<0>(m_nodeType_WithChildren))
        .WillOnce(SetArgReferee<0>(m_nodeType_WithValue))
        .WillOnce(SetArgReferee<0>(m_nodeType_WithValue))
        .WillOnce(SetArgReferee<0>(m_nodeType_WithValue));

    EXPECT_CALL(deserializerMock, deserialize(An<unsigned &>()))
            .WillOnce(SetArgReferee<0>(numOfChildrenNodeWithChild))
            .WillOnce(SetArgReferee<0>(numOfChildren))
            .WillOnce(SetArgReferee<0>(numOfChildren))
            .WillOnce(SetArgReferee<0>(numOfChildren));

    EXPECT_CALL(deserializerMock, deserialize(An<QString &>())).WillOnce(SetArgReferee<0>(mainNodeName));

    serializer.deserialize(deserializerMock, nodeWithChildren);

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

    QMap<quint8, QVariant> infos;
    EXPECT_CALL(*infosDeserializer, deserialize(_,_)).Times(9).WillRepeatedly(SetArgReferee<1>(infos));
    EXPECT_CALL(deserializerMock, deserialize(An<quint8 &>()))
        .WillOnce(SetArgReferee<0>(m_nodeType_WithChildren))
        .WillOnce(SetArgReferee<0>(m_nodeType_WithChildren))
        .WillOnce(SetArgReferee<0>(m_nodeType_WithValue))
        .WillOnce(SetArgReferee<0>(m_nodeType_WithValue))
        .WillOnce(SetArgReferee<0>(m_nodeType_WithValue))
        .WillOnce(SetArgReferee<0>(m_nodeType_WithChildren))
        .WillOnce(SetArgReferee<0>(m_nodeType_WithValue))
        .WillOnce(SetArgReferee<0>(m_nodeType_WithValue))
        .WillOnce(SetArgReferee<0>(m_nodeType_WithValue));

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

    serializer.deserialize(deserializerMock, nodeWithChildren);

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



