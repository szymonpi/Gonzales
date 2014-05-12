#include "QAsToLearnProvider.h"
#include "../Common/SimpleTree/node.h"
#include <memory>

QAsToLearnProvider::QAsToLearnProvider(std::shared_ptr<QAsProvider> qasProvider):
    m_qasProvider(qasProvider)
{
}

bool QAsToLearnProvider::canBeThereSomethingToLearn(const SimpleTree::Node<QA> &rootNode) const
{
    return rootNode.size() != 0 || rootNode.getNodeValue().get();
}

QQueue<std::shared_ptr<QA> > QAsToLearnProvider::getQAs()
{
    SimpleTree::Node<QA> &rootNode= m_qasProvider->getQAs();
    if(!canBeThereSomethingToLearn(rootNode))
        throw std::logic_error("No QA to learn in repository");

    QQueue<std::shared_ptr<QA> > qas;
    fillQAsToLearn(qas, rootNode);
    return qas;
}

void QAsToLearnProvider::fillQAsToLearn(QQueue<std::shared_ptr<QA> > &qasToLearn,
                    const SimpleTree::Node<QA> &node) const
{
    if(node.getNodeValue().get())
        if(node.getNodeValue()->toLearn() == true)
            qasToLearn.push_back(node.getNodeValue());
    foreach(const SimpleTree::Node<QA> node, node.getNodes())
    {
        fillQAsToLearn(qasToLearn, node);
    }
}

