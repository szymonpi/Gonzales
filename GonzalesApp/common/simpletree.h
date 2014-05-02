#ifndef SIMPLETREE_H
#define SIMPLETREE_H
#include <vector>
#include <memory>
#include <QString>
#include "qtproxies/fileserializer.h"
#include "qtproxies/filedeserializer.h"

template <typename T>
class Node
{
public:

    Node(const std::shared_ptr<T> &nodeValue = std::shared_ptr<T>())
    {
        m_value = nodeValue;
    }
    void appendNodes(const std::vector<Node<T> > &nodes)
    {
        m_nodes.insert(m_nodes.end(), nodes.begin(), nodes.end());
    }
    void appendNode(const Node<T> node)
    {
        m_nodes.push_back(node);
    }
    void removeNode(const T& index)
    {
        typename std::vector<Node<T> >::iterator it = m_nodes.begin()+index;
        m_nodes.erase(it);
    }
    std::vector<Node<T> > &getNodes()
    {
        return m_nodes;
    }
    const std::vector<Node<T> > &getNodes() const
    {
        return m_nodes;
    }
    Node<T> &getNode(unsigned index)
    {
        return m_nodes.at(index);
    }
    void setName(const QString &name)
    {
        m_name = name;
    }
    QString getName() const
    {
        return m_name;
    }

    unsigned size() const
    {
        return m_nodes.size();
    }

    void appendNodeValue(const std::shared_ptr<T> &nodeValue)
    {
        m_value = nodeValue;
    }

    void emplaceNode(const std::shared_ptr<T> &nodeValue)
    {
        Node<T> node(nodeValue);
        m_nodes.push_back(node);
    }

    std::shared_ptr<T> getNodeValue() const
    {
        return m_value;
    }

    std::shared_ptr<T> operator->()
    {
        return m_value;
    }

    std::shared_ptr<T> operator*()
    {
        return m_value;
    }

    bool operator==(const Node<T>& otherNode) const
    {
        if(m_name!=m_name)
            return false;
        if(m_nodes.size() != otherNode.size())
            return false;
        if(m_value.get() && !otherNode.getNodeValue().get())
            return false;
        if(!m_value.get() && otherNode.getNodeValue().get())
            return false;

        auto otherNodes = otherNode.getNodes();
        for(int i=0; i<m_nodes.size(); i++)
        {
            if(!(m_nodes.at(i)==otherNodes.at(i)))
                return false;
        }
        return true;
    }


private:
    QString m_name;
    std::shared_ptr<T> m_value;
    std::vector<Node<T> > m_nodes;
};

namespace SimpleTree
{

enum
{
    NodeType_Empty = 0,
    NodeType_WithChildren = 1,
    NodeType_WithValue = 2
};

class ValueFactory
{
public:

    template<class T>
    static std::shared_ptr<T> create()
    {
        return std::make_shared<T>();
    }
};

template<typename T>
static void deserialize(CanDeserializeData &deserializer, Node<T> &node)
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
quint8 concludeNodeType(const Node<T> &node)
{
    quint8 nodeType = NodeType_Empty;
    if(node.getNodeValue().get())
        nodeType |= NodeType_WithValue;
    if(node.size() > 0)
        nodeType |= NodeType_WithChildren;
    return nodeType;
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

}

#endif // SIMPLETREE_H
