
#include "../gtest.h"
#include "../gmock.h"
#include "../../GonzalesApp/common/SimpleTree/NodeSerializer.h"
#include "../AQImporter/DataDeserializerMock.h"
#include "../AQImporter/DataSerializerMock.h"
#include "../CommonUtUtilities/PrintTo.h"
#include "../CommonUtUtilities/CommonMocks.h"
#include <QString>
#include <QVariant>
#include "../../GonzalesApp/common/Common.h"
#include "InfosDeserializerMock.h"

using namespace testing;
using namespace SimpleTree;
using namespace SimpleTree::Utils;

class SerializationTestSuite: public testing::Test
{
public:
    SerializationTestSuite():
        serializer(infosSerializer)
    {
        nodeWithValue.appendNodeValue(nodeValue);
    }

    StrictMock<DataSerializerMock> serializerMock;
    unsigned numOfChildrenContaining2Nodes = 2;
    unsigned numOfChildrenContaining3Nodes = 3;
    unsigned numOfChildrenNotContaining = 0;
    std::shared_ptr<NodeValueMock> nodeValue = std::make_shared<NodeValueMock>();
    std::shared_ptr<NodeValueMock> nodeValue2 = std::make_shared<NodeValueMock>();
    std::shared_ptr<NodeValueMock> nodeValue3 = std::make_shared<NodeValueMock>();
    std::shared_ptr<NodeValueMock> nodeValue4 = std::make_shared<NodeValueMock>();
    std::shared_ptr<NodeValueMock> nodeValue5 = std::make_shared<NodeValueMock>();
    std::shared_ptr<NodeValueMock> nodeValue6 = std::make_shared<NodeValueMock>();
    std::shared_ptr<StrictMock<InfosSerializerMock>> infosSerializer = std::make_shared<StrictMock<InfosSerializerMock>>();
    Node<NodeValueMock> nodeWithValue;
    NodeSerializer serializer;
};

TEST_F(SerializationTestSuite, serializeOneNodeWithValue)
{
    EXPECT_CALL(serializerMock, serialize(TypedEq<unsigned>(numOfChildrenNotContaining)));
    EXPECT_CALL(serializerMock, serialize(TypedEq<quint8>(NodeType_WithValue)));
    EXPECT_CALL(*infosSerializer, serialize(_,_));
    EXPECT_CALL(*nodeValue, serialize(_));
    serializer.serialize(serializerMock, nodeWithValue);
}

TEST_F(SerializationTestSuite, serializeOneNodeWithValueAndInfos)
{
    nodeWithValue.setInfo(NODE_INFO_ROLE_CHECKED, true);
    nodeWithValue.setInfo(99, 45);
    nodeWithValue.setInfo(100, QString("testing string"));
    nodeWithValue.setInfo(101, 4.56);
    EXPECT_CALL(serializerMock, serialize(TypedEq<unsigned>(numOfChildrenNotContaining)));
    EXPECT_CALL(*infosSerializer, serialize(_,_));

    EXPECT_CALL(serializerMock, serialize(TypedEq<quint8>(NodeType_WithValue)));
    EXPECT_CALL(*nodeValue, serialize(_));
    serializer.serialize(serializerMock, nodeWithValue);
}

TEST_F(SerializationTestSuite, serializeOneNodeWithValueAndUnsupportedInfoTypeShouldThrow)
{

    EXPECT_CALL(serializerMock, serialize(TypedEq<quint8>(NodeType_WithValue)));
    EXPECT_CALL(*infosSerializer, serialize(_,_)).WillOnce(Throw(std::logic_error("")));
    ASSERT_THROW(serializer.serialize(serializerMock, nodeWithValue), std::logic_error);
}

TEST_F(SerializationTestSuite, serializeTwoItemsInOneNode)
{
    Node<NodeValueMock> node1(nodeValue);
    Node<NodeValueMock> node2(nodeValue2);

    Node<NodeValueMock> mainNode;
    std::string nodeName = "ContainingNode";
    mainNode.setName(nodeName);
    mainNode.appendNode(node1);
    mainNode.appendNode(node2);

    EXPECT_CALL(*infosSerializer, serialize(_,_)).Times(3);
    EXPECT_CALL(serializerMock, serialize(TypedEq<quint8>(NodeType_WithChildren)));
    EXPECT_CALL(serializerMock, serialize(TypedEq<unsigned>(numOfChildrenContaining2Nodes)));
    EXPECT_CALL(serializerMock, serialize(TypedEq<const std::string &>(nodeName)));

    EXPECT_CALL(serializerMock, serialize(TypedEq<unsigned>(numOfChildrenNotContaining))).Times(2);
    EXPECT_CALL(serializerMock, serialize(TypedEq<quint8>(NodeType_WithValue))).Times(2);
    EXPECT_CALL(*nodeValue, serialize(_));
    EXPECT_CALL(*nodeValue2, serialize(_));
    serializer.serialize(serializerMock, mainNode);
}

TEST_F(SerializationTestSuite, serializeSixItemsInThreeNodes)
{
    Node<NodeValueMock> node1(nodeValue);
    Node<NodeValueMock> node2(nodeValue2);
    Node<NodeValueMock> node3(nodeValue3);
    Node<NodeValueMock> node4(nodeValue4);
    Node<NodeValueMock> node5(nodeValue5);
    Node<NodeValueMock> node6(nodeValue6);

    Node<NodeValueMock> continingNode1;
    std::string containingNode1Name = "ContainingNode1";
    continingNode1.setName(containingNode1Name);
    continingNode1.appendNode(node1);
    continingNode1.appendNode(node2);
    Node<NodeValueMock> continingNode2;
    std::string containingNode2Name = "ContainingNode2";
    continingNode2.setName(containingNode2Name);
    continingNode2.appendNode(node3);
    continingNode2.appendNode(node4);
    Node<NodeValueMock> continingNode3;
    std::string containingNode3Name = "ContainingNode3";
    continingNode3.setName(containingNode3Name);
    continingNode3.appendNode(node5);
    continingNode3.appendNode(node6);

    Node<NodeValueMock> mainNode;
    std::string mainNodeName = "ContainingNode";
    mainNode.setName(mainNodeName);
    mainNode.appendNode(continingNode1);
    mainNode.appendNode(continingNode2);
    mainNode.appendNode(continingNode3);


    EXPECT_CALL(*infosSerializer, serialize(_,_)).Times(10);
    EXPECT_CALL(serializerMock, serialize(TypedEq<quint8>(NodeType_WithChildren))).Times(4);
    EXPECT_CALL(serializerMock, serialize(TypedEq<quint8>(NodeType_WithValue))).Times(6);


    EXPECT_CALL(serializerMock, serialize(TypedEq<unsigned>(numOfChildrenNotContaining))).Times(6);
    EXPECT_CALL(serializerMock, serialize(TypedEq<unsigned>(numOfChildrenContaining3Nodes)));
    EXPECT_CALL(serializerMock, serialize(TypedEq<unsigned>(numOfChildrenContaining2Nodes))).Times(3);

    EXPECT_CALL(serializerMock, serialize(TypedEq<const std::string &>(mainNodeName)));
    EXPECT_CALL(serializerMock, serialize(TypedEq<const std::string &>(containingNode1Name)));
    EXPECT_CALL(serializerMock, serialize(TypedEq<const std::string &>(containingNode2Name)));
    EXPECT_CALL(serializerMock, serialize(TypedEq<const std::string &>(containingNode3Name)));
    EXPECT_CALL(*nodeValue, serialize(_));
    EXPECT_CALL(*nodeValue2, serialize(_));
    EXPECT_CALL(*nodeValue3, serialize(_));
    EXPECT_CALL(*nodeValue4, serialize(_));
    EXPECT_CALL(*nodeValue5, serialize(_));
    EXPECT_CALL(*nodeValue6, serialize(_));
    serializer.serialize(serializerMock, mainNode);
}



