#pragma once

class IQANodeSerializer
{
public:
    virtual void serialize(IDataSerializer& serializer, const SimpleTree::Node<QA> &node) = 0;
    virtual ~IQANodeSerializer(){}
};

