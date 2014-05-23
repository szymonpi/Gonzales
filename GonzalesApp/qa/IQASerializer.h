#pragma once

class IQASerializer
{
public:
    virtual void serialize(IDataSerializer& serializer, const SimpleTree::Node<QA> &node) = 0;
    virtual ~IQASerializer(){}
};

