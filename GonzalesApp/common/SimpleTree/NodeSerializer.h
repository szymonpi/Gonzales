#pragma once
#include "IInfosSerializer.h"
#include "Utils.h"
#include <memory>
#include "Node.h"

namespace SimpleTree
{

namespace Utils
{

class NodeSerializer
{
public:
    NodeSerializer(std::shared_ptr<IInfosSerializer> infosSerializer):
        infosSerializer(infosSerializer)
    {
    }

template<typename T>
void deserialize(IDataDeserializer& deserializer, Node<T> &node)
{
    quint8 nodeType = getNodeType(deserializer);
    node.setInfos(getInfos(deserializer));
    unsigned numOfChildren = getNumOfChildren(deserializer);

    if(nodeType & NodeType_WithValue)
    {
        node.appendNodeValue(deserializeValue<T>(deserializer));
    }
    if(nodeType & NodeType_WithChildren)
    {
        node.setName(getName(deserializer));
        deserializeChildren(deserializer, node, numOfChildren);
    }
}

template<typename T>
void serialize(IDataSerializer &serializer, const Node<T> &node)
{
    quint8 nodeType = concludeNodeType(node);
    serializer.serialize(nodeType);
    infosSerializer->serialize(serializer, node.getInfos());
    serializer.serialize(node.size());
    if(node.size()==0)
        node.getNodeValue()->serialize(serializer);
    else
    {
        serializer.serialize(node.getName());
        foreach(const Node<T> &node, node.getNodes())
        {
            serialize(serializer, node);
        }
    }
}

private:

quint8 getNodeType(IDataDeserializer& deserializer)
{
    quint8 nodeType;
    deserializer.deserialize(nodeType);
    if(nodeType == NodeType_Empty)
        throw std::logic_error("Can't import empty node");
    return nodeType;
}

QMap<quint8, QVariant> getInfos(IDataDeserializer& deserializer)
{
    QMap<quint8, QVariant> infos;
    infosSerializer->deserialize(deserializer, infos);
    return infos;
}

unsigned getNumOfChildren(IDataDeserializer& deserializer)
{
    unsigned numOfChildren = 0;
    deserializer.deserialize(numOfChildren);
    return numOfChildren;
}

template<typename T>
std::shared_ptr<T> deserializeValue(IDataDeserializer& deserializer)
{
    std::shared_ptr<T> value = std::make_shared<T>();
    value->deserialize(deserializer);
    return value;
}

QString getName(IDataDeserializer& deserializer)
{
    QString nodeName;
    deserializer.deserialize(nodeName);
    return nodeName;
}

template<typename T>
void deserializeChildren(IDataDeserializer& deserializer, Node<T> &node, unsigned numOfChildren)
{
    for(int i = 0; i < numOfChildren; ++i)
    {
        Node<T> childNode;
        deserialize(deserializer, childNode);
        node.appendNode(childNode);
    }
}

template<typename T>
inline quint8 concludeNodeType(const Node<T> &node)
{
    quint8 nodeType = NodeType_Empty;
    if(node.getNodeValue().get())
        nodeType |= NodeType_WithValue;
    if(node.size() > 0)
        nodeType |= NodeType_WithChildren;
    return nodeType;
}

std::shared_ptr<IInfosSerializer> infosSerializer;

};

}

}

