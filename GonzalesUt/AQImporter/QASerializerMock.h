#ifndef QASERIALIZERMOCK_H
#define QASERIALIZERMOCK_H

#include "../gmock.h"
#include "../../GonzalesApp/qa/QASerializer.h"

class QASerializerMock : public IQASerializer
{
public:
    MOCK_METHOD2(serialize, void(CanSerializeData&, SimpleTree::Node<QA>));
};

class QADeserializerMock : public IQADeserializer
{
public:
    MOCK_METHOD2(deserialize, void(CanDeserializeData&, SimpleTree::Node<QA>));
};

#endif // QASERIALIZERMOCK_H
