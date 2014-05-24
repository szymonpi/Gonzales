
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

class InfosSerializationTestSuite: public testing::Test
{
public:
    InfosSerializer serializer;
    int expectedInfosSize_1 = 1;
    int expectedInfosSize_3 = 3;
    quint8 expectedKey_0 = 0;
    quint8 expectedKey_1 = 1;
    quint8 expectedKey_2 = 2;

    unsigned expectedType_Uint = QVariant::UInt;
    unsigned expectedType_Int = QVariant::Int;
    unsigned expectedType_Bool = QVariant::Bool;
    unsigned expectedType_LongLong = QVariant::LongLong;
    unsigned expectedType_ULongLong = QVariant::ULongLong;
    unsigned expectedType_Double = QVariant::Double;
    unsigned expectedType_String = QVariant::String;

    unsigned expectedValue_uint = 4;
    int expectedValue_Int = -89;
    long long int expectedValue_LongLong = -4294967200;
    unsigned long long int expectedValue_ULongLong = 8294967200;
    double expectedValue_Double = 1234.890;
    QString expectedValue_String = "str";
    bool expectedValue_bool = true;
    std::shared_ptr<StrictMock<DataSerializerMock>> dataSerializerMock = std::make_shared<StrictMock<DataSerializerMock>>();


    template <class T>
    void setExpectationsForSerialize(int infoSize, quint8 expectedKey, unsigned expectedType, T expectedValue)
    {
        EXPECT_CALL(*dataSerializerMock, serialize(TypedEq<int>(infoSize)));
        EXPECT_CALL(*dataSerializerMock, serialize(TypedEq<quint8>(expectedKey)));
        EXPECT_CALL(*dataSerializerMock, serialize(TypedEq<unsigned>(expectedType)));
        EXPECT_CALL(*dataSerializerMock, serialize(TypedEq<T>(expectedValue)));
    }
};

TEST_F(InfosSerializationTestSuite, emptyInfosMapGiven_shouldntSerializeAnything)
{
    QMap<quint8, QVariant> infosMap;
    EXPECT_CALL(*dataSerializerMock, serialize(TypedEq<int>(0)));
    serializer.serialize(*dataSerializerMock, infosMap);
}

TEST_F(InfosSerializationTestSuite, OneBoolInfoGiven_shouldSerializeInfo)
{
    QMap<quint8, QVariant> infosMap;
    infosMap[expectedKey_0] = expectedValue_bool;
    setExpectationsForSerialize(expectedInfosSize_1, expectedKey_0, expectedType_Bool, expectedValue_bool);
    serializer.serialize(*dataSerializerMock, infosMap);
}

TEST_F(InfosSerializationTestSuite, OneUIntInfoGiven_shouldSerializeInfo)
{
    QMap<quint8, QVariant> infosMap;
    infosMap[expectedKey_0] = expectedValue_uint;
    setExpectationsForSerialize(expectedInfosSize_1, expectedKey_0, expectedType_Uint, expectedValue_uint);
    serializer.serialize(*dataSerializerMock, infosMap);
}

TEST_F(InfosSerializationTestSuite, OneIntInfoGiven_shouldSerializeInfo)
{
    QMap<quint8, QVariant> infosMap;
    infosMap[expectedKey_0] = expectedValue_Int;
    setExpectationsForSerialize(expectedInfosSize_1, expectedKey_0, expectedType_Int, expectedValue_Int);
    serializer.serialize(*dataSerializerMock, infosMap);
}

TEST_F(InfosSerializationTestSuite, OneLongLongInfoGiven_shouldSerializeInfo)
{
    QMap<quint8, QVariant> infosMap;
    infosMap[expectedKey_0] = expectedValue_LongLong;
    setExpectationsForSerialize(expectedInfosSize_1, expectedKey_0, expectedType_LongLong, expectedValue_LongLong);
    serializer.serialize(*dataSerializerMock, infosMap);
}

TEST_F(InfosSerializationTestSuite, OneULongLongInfoGiven_shouldSerializeInfo)
{
    QMap<quint8, QVariant> infosMap;
    infosMap[expectedKey_0] = expectedValue_ULongLong;
    setExpectationsForSerialize(expectedInfosSize_1, expectedKey_0, expectedType_ULongLong, expectedValue_ULongLong);
    serializer.serialize(*dataSerializerMock, infosMap);
}

TEST_F(InfosSerializationTestSuite, OneDoubleInfoGiven_shouldSerializeInfo)
{
    QMap<quint8, QVariant> infosMap;
    infosMap[expectedKey_0] = expectedValue_Double;
    setExpectationsForSerialize(expectedInfosSize_1, expectedKey_0, expectedType_Double, expectedValue_Double);
    serializer.serialize(*dataSerializerMock, infosMap);
}

TEST_F(InfosSerializationTestSuite, OneStringInfoGiven_shouldSerializeInfo)
{
    QMap<quint8, QVariant> infosMap;
    infosMap[expectedKey_0] = expectedValue_String;
    setExpectationsForSerialize<const QString &>(expectedInfosSize_1, expectedKey_0, expectedType_String, expectedValue_String);
    serializer.serialize(*dataSerializerMock, infosMap);
}

TEST_F(InfosSerializationTestSuite, ThreeStringInfoGiven_shouldSerializeInfo)
{
    QMap<quint8, QVariant> infosMap;
    infosMap[expectedKey_0] = expectedValue_String;
    infosMap[expectedKey_1] = expectedValue_String;
    infosMap[expectedKey_2] = expectedValue_String;

    EXPECT_CALL(*dataSerializerMock, serialize(TypedEq<int>(expectedInfosSize_3)));

    EXPECT_CALL(*dataSerializerMock, serialize(TypedEq<quint8>(expectedKey_0)));
    EXPECT_CALL(*dataSerializerMock, serialize(TypedEq<unsigned>(expectedType_String))).Times(3);
    EXPECT_CALL(*dataSerializerMock, serialize(TypedEq<const QString &>(expectedValue_String))).Times(3);

    EXPECT_CALL(*dataSerializerMock, serialize(TypedEq<quint8>(expectedKey_1)));
    EXPECT_CALL(*dataSerializerMock, serialize(TypedEq<quint8>(expectedKey_2)));

    serializer.serialize(*dataSerializerMock, infosMap);
}

TEST_F(InfosSerializationTestSuite, OneUnsupportedInfoGiven_shouldSerializeInfo)
{
    QMap<quint8, QVariant> infosMap;
    infosMap[expectedKey_0] = QStringList();
    EXPECT_CALL(*dataSerializerMock, serialize(TypedEq<int>(expectedInfosSize_1)));

    EXPECT_THROW(serializer.serialize(*dataSerializerMock, infosMap), std::logic_error);
}
