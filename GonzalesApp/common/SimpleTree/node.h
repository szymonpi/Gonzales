#pragma once
#include <vector>
#include <memory>
#include <QString>
#include "../qtproxies/fileserializer.h"
#include "../qtproxies/filedeserializer.h"

namespace SimpleTree
{

template <typename T>
class Node
{
public:

    Node(const std::shared_ptr<T> &nodeValue = std::shared_ptr<T>())
    {
        m_value = nodeValue;
    }
    void appendNodes(const std::vector<SimpleTree::Node<T> > &nodes)
    {
        m_nodes.insert(m_nodes.end(), nodes.begin(), nodes.end());
    }
    void appendNode(const Node<T> node)
    {
        m_nodes.push_back(node);
    }
    void removeNode(const T& index)
    {
        typename std::vector<SimpleTree::Node<T> >::iterator it = m_nodes.begin()+index;
        m_nodes.erase(it);
    }
    std::vector<SimpleTree::Node<T> > &getNodes()
    {
        return m_nodes;
    }
    const std::vector<SimpleTree::Node<T> > &getNodes() const
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
    std::vector<SimpleTree::Node<T> > m_nodes;
};

}
