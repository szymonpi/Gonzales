#include "QAsToLearnCheckedByUserProvider.h"
#include "../../common/Common.h"

QAsToLearnCheckedByUserProvider::QAsToLearnCheckedByUserProvider(std::shared_ptr<QAsProvider> qasProvider):
    m_qasProvider(qasProvider)
{
}

bool QAsToLearnCheckedByUserProvider::canBeThereSomethingToLearn(const SimpleTree::Node<QA> &rootNode) const
{
    return rootNode.size() != 0 || rootNode.getNodeValue().get();
}

std::vector<std::shared_ptr<QA> > QAsToLearnCheckedByUserProvider::getQAs()
{
    SimpleTree::Node<QA> &rootNode= m_qasProvider->getQAs();
    if(!canBeThereSomethingToLearn(rootNode))
        throw std::logic_error("No QA to learn in repository");

    std::vector<std::shared_ptr<QA> > qas;
    fillQAsToLearn(qas, rootNode);
    return qas;
}

void QAsToLearnCheckedByUserProvider::fillQAsToLearn(std::vector<std::shared_ptr<QA> > &qasToLearn,
                    const SimpleTree::Node<QA> &node) const
{
    if(node.getNodeValue().get())
        if(node.getInfo(NODE_INFO_ROLE_CHECKED) == true && node.getNodeValue().get())
            qasToLearn.push_back(node.getNodeValue());
    foreach(const SimpleTree::Node<QA> node, node.getNodes())
    {
        fillQAsToLearn(qasToLearn, node);
    }
}
