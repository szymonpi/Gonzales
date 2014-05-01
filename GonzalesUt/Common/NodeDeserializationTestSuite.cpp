
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
    std::shared_ptr<NodeValueMock> value = std::make_shared<NodeValueMock>();
    quint8 nodeTypeEmpty = SimpleTree::NodeType_Empty;
    quint8 nodeTypeWithValue = SimpleTree::NodeType_WithValue;
    quint8 nodeTypeWithChildren = SimpleTree::NodeType_WithChildren;

};

TEST_F(DeserializationTestSuite, DeserializeOneEmptyNode)
{
    Node<NodeValueMock> node;

    EXPECT_CALL(deserializerMock, deserialize(An<quint8 &>())).WillOnce(SetArgReferee<0>(nodeTypeEmpty));
    EXPECT_THROW(SimpleTree::deserialize(deserializerMock, node), std::logic_error);
}

TEST_F(DeserializationTestSuite, DeserializeOneNodeWithValue)
{
    Node<NodeValueMock> node(value);

    unsigned numOfChildren = 0;

    EXPECT_CALL(deserializerMock, deserialize(An<quint8 &>())).WillOnce(SetArgReferee<0>(nodeTypeWithValue));
    EXPECT_CALL(deserializerMock, deserialize(TypedEq<unsigned &>(numOfChildren))).WillOnce(SetArgReferee<0>(0));

    SimpleTree::deserialize(deserializerMock, node);
}




