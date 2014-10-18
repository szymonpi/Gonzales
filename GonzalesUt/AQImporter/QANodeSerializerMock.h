#pragma once

#include "../gmock.h"
#include "../../GonzalesApp/qa/qaio/QANodeSerializer.h"

class QANodeSerializerMock : public IQANodeSerializer
{
public:
    MOCK_METHOD2(serialize, void(IDataSerializer&, const SimpleTree::Node<QA>&));
};

class QADeserializerMock : public IQANodeDeserializer
{
public:
    MOCK_METHOD2(deserialize, void(IDataDeserializer&, SimpleTree::Node<QA>&));
};

