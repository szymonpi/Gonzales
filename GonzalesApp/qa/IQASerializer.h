#pragma once

class IQASerializer
{
public:
    virtual void serialize(CanSerializeData& serializer, const SimpleTree::Node<QA> &node) = 0;
    virtual ~IQASerializer(){}
};

