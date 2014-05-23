#pragma once
#include "../../GonzalesApp/common/qtproxies/IDataDeserializer.h"
#include "../../GonzalesApp/common/qtproxies/IDataSerializer.h"

class NodeValue
{
public:
    virtual void serialize(IDataSerializer &serializer) = 0;
    virtual void deserialize(IDataDeserializer &deserializer) = 0;
};

class NodeValueStub: public NodeValue
{
public:
    virtual void serialize(IDataSerializer &serializer)
    {

    }

    virtual void deserialize(IDataDeserializer &deserializer)
    {

    }
};

class NodeValueMock: public NodeValue
{
public:
    MOCK_METHOD1(serialize, void(IDataSerializer &));
    MOCK_METHOD1(deserialize, void(IDataDeserializer &));
};

