#ifndef UTILS_H
#define UTILS_H
#include "Node.h"


namespace SimpleTree
{

namespace Utils
{

enum
{
    NodeType_Empty = 0,
    NodeType_WithChildren = 1,
    NodeType_WithValue = 2
};

class NodeSerializer
{
public:
template<typename T>
void deserialize(CanDeserializeData &deserializer, Node<T> &node)
{
    unsigned numOfChildren = 0;
    quint8 nodeType;
    deserializer.deserialize(nodeType);
    if(nodeType == NodeType_Empty)
        throw std::logic_error("Can't import empty node");

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
void serialize(CanSerializeData &serializer, const Node<T> &node)
{
    quint8 nodeType = concludeNodeType(node);
    serializer.serialize(nodeType);
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

};

}

}

#endif // UTILS_H
