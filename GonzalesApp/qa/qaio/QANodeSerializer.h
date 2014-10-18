#pragma once
#include "../../common/SimpleTree/NodeSerializer.h"
#include "../../common/qtproxies/DataSerializer.h"
#include "../../common/qtproxies/DataDeserializer.h"
#include "../../common/SimpleTree/InfosSerializer.h"
#include "IQANodeSerializer.h"

class IQANodeDeserializer
{
public:
    virtual void deserialize(IDataDeserializer &deserializer, SimpleTree::Node<QA> &node) = 0;
    virtual ~IQANodeDeserializer(){}
};

class QANodeSerializer: public IQANodeSerializer, public IQANodeDeserializer
{
public:
    QANodeSerializer():
        serializer{std::make_shared<SimpleTree::Utils::InfosSerializer>()}
    {}
    void serialize(IDataSerializer& DataSerializer, const SimpleTree::Node<QA> &node)
    {
        serializer.serialize(DataSerializer, node);
    }

    void deserialize(IDataDeserializer &DataDeserializer, SimpleTree::Node<QA> &node)
    {
        serializer.deserialize(DataDeserializer, node);
    }

private:
    SimpleTree::Utils::NodeSerializer serializer;
};
