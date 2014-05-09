#ifndef QASERIALIZER_H
#define QASERIALIZER_H
#include "../Common/SimpleTree/utils.h"
#include "../Common/qtproxies/fileserializer.h"
#include "../Common/qtproxies/filedeserializer.h"
#include "../Common/qtproxies/fileserializer.h"

class IQASerializer
{
public:
    virtual void serialize(CanSerializeData& serializer, const SimpleTree::Node<QA> &node) = 0;
    virtual ~IQASerializer(){}
};

class IQADeserializer
{
public:
    virtual void deserialize(CanDeserializeData &deserializer, SimpleTree::Node<QA> &node) = 0;
    virtual ~IQADeserializer(){}
};

class QASerializer: public IQASerializer, public IQADeserializer
{
public:
    void serialize(CanSerializeData& fileSerializer, const SimpleTree::Node<QA> &node)
    {

        serializer.serialize(fileSerializer, node);
    }

    void deserialize(CanDeserializeData &fileDeserializer, SimpleTree::Node<QA> &node)
    {
        SimpleTree::Utils::NodeSerializer serializer;
        serializer.deserialize(fileDeserializer, node);
    }

private:
    SimpleTree::Utils::NodeSerializer serializer;
};

#endif // QASERIALIZER_H
