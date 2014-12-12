
#include "../gtest.h"
#include "../gmock.h"
#include "../AQImporter/DataDeserializerMock.h"
#include "../AQImporter/DataSerializerMock.h"
#include "../CommonUtUtilities/PrintTo.h"
#include "../CommonUtUtilities/CommonMocks.h"
#include <QString>
#include <QVariant>
#include "../../GonzalesApp/common/Common.h"
#include "../../GonzalesApp/common/SimpleTree/InfosSerializer.h"
#include "../AQImporter/DataDeserializerMock.h"
#include "../AQImporter/DataSerializerMock.h"
#include <memory>

using namespace testing;
using namespace SimpleTree;
using namespace SimpleTree::Utils;

class InfosDeserializationTestSuite: public testing::Test
{
public:
    InfosSerializer serializer;
    std::shared_ptr<StrictMock<DataDeserializerMock>> dataDeserializerMock = std::make_shared<StrictMock<DataDeserializerMock>>();

};

TEST_F(InfosDeserializationTestSuite, ShouldntDeserializeAnyInfo)
{
    std::map<quint8, QVariant> infosMap;
    int infosSize = 0;
    EXPECT_CALL(*dataDeserializerMock, deserialize(An<int&>())).WillOnce(SetArgReferee<0>(infosSize));
    serializer.deserialize(*dataDeserializerMock, infosMap);
}

TEST_F(InfosDeserializationTestSuite, ShouldDeserializeOneBoolInfo)
{
    std::map<quint8, QVariant> infosMap;
    int infosSize = 1;
    quint8 nodeInfoRole = 1;
    unsigned type = QVariant::Bool;
    QVariant valueVariant = true;
    EXPECT_CALL(*dataDeserializerMock, deserialize(An<int&>())).WillOnce(SetArgReferee<0>(infosSize));
    EXPECT_CALL(*dataDeserializerMock, deserialize(An<quint8&>())).WillOnce(SetArgReferee<0>(nodeInfoRole));
    EXPECT_CALL(*dataDeserializerMock, deserialize(An<unsigned&>())).WillOnce(SetArgReferee<0>(type));
    EXPECT_CALL(*dataDeserializerMock, deserialize(An<bool&>())).WillOnce(SetArgReferee<0>(valueVariant.toBool()));

    serializer.deserialize(*dataDeserializerMock, infosMap);
}

TEST_F(InfosDeserializationTestSuite, ShouldDeserializeUintOneInfo)
{
    std::map<quint8, QVariant> infosMap;
    int infosSize = 1;
    quint8 nodeInfoRole = 1;
    unsigned type = QVariant::UInt;
    QVariant valueVariant = 57;
    EXPECT_CALL(*dataDeserializerMock, deserialize(An<int&>())).WillOnce(SetArgReferee<0>(infosSize));
    EXPECT_CALL(*dataDeserializerMock, deserialize(An<quint8&>())).WillOnce(SetArgReferee<0>(nodeInfoRole));
    EXPECT_CALL(*dataDeserializerMock, deserialize(An<unsigned&>()))
                .WillOnce(SetArgReferee<0>(type))
                .WillOnce(SetArgReferee<0>(valueVariant.toUInt()));

    serializer.deserialize(*dataDeserializerMock, infosMap);
}

TEST_F(InfosDeserializationTestSuite, ShouldDeserializeIntOneInfo)
{
    std::map<quint8, QVariant> infosMap;
    int infosSize = 1;
    quint8 nodeInfoRole = 1;
    unsigned type = QVariant::Int;
    QVariant valueVariant = -678;
    EXPECT_CALL(*dataDeserializerMock, deserialize(An<int&>()))
            .WillOnce(SetArgReferee<0>(infosSize))
            .WillOnce(SetArgReferee<0>(valueVariant.toInt()));
    EXPECT_CALL(*dataDeserializerMock, deserialize(An<quint8&>())).WillOnce(SetArgReferee<0>(nodeInfoRole));
    EXPECT_CALL(*dataDeserializerMock, deserialize(An<unsigned&>())).WillOnce(SetArgReferee<0>(type));

    serializer.deserialize(*dataDeserializerMock, infosMap);
}
