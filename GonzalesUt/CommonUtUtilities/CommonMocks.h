#ifndef COMMONMOCKS_H
#define COMMONMOCKS_H


class NodeValue
{
public:
    virtual void serialize(CanSerializeData &serializer) = 0;
    virtual void deserialize(CanDeserializeData &deserializer) = 0;
};

class NodeValueStub: public NodeValue
{
public:
    virtual void serialize(CanSerializeData &serializer)
    {

    }

    virtual void deserialize(CanDeserializeData &deserializer)
    {

    }
};

class NodeValueMock: public NodeValue
{
public:
    MOCK_METHOD1(serialize, void(CanSerializeData &));
    MOCK_METHOD1(deserialize, void(CanDeserializeData &));
};

#endif // COMMONMOCKS_H
