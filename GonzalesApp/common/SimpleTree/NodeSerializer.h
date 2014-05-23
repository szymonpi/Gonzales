#pragma once
#include "InfosSerializer.h"
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
void deserialize(IDataDeserializer&deserializer, Node<T> &node)
{
    unsigned numOfChildren = 0;
    quint8 nodeType;
    deserializer.deserialize(nodeType);
    if(nodeType == NodeType_Empty)
        throw std::logic_error("Can't import empty node");

    QMap<quint8, QVariant> infos;
    infosSerializer->deserialize(deserializer, infos);
    node.setInfos(infos);

    deserializer.deserialize(numOfChildren);
    if(nodeType & NodeType_WithValue)
    {
        std::shared_ptr<T> value = std::make_shared<T>();
        value->deserialize(deserializer);
        node.appendNodeValue(value);
    }
    if(nodeType & NodeType_WithChildren)
    {
        QString nodeName;
        deserializer.deserialize(nodeName);
        node.setName(nodeName);
        for(int i = 0; i < numOfChildren; ++i)
        {
            Node<T> childNode;
            deserialize(deserializer, childNode);
            node.appendNode(childNode);
        }
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

