#include "QAsToLearnByUserChecker.h"
#include "../../common/Common.h"


QAsToLearnByUserChecker::QAsToLearnByUserChecker(std::shared_ptr<IQARepository> qAsProvider):
    m_qARepository(qAsProvider)
{

}

void QAsToLearnByUserChecker::select(const QTreeWidgetItem &item)
{
    if(item.childCount() == 0)
        return;
    selectItem(item, m_qARepository->getQAs(), isSelected(item));
}

void QAsToLearnByUserChecker::selectItem(const QTreeWidgetItem &item, SimpleTree::Node<QA> &rootNode, const bool select)
{
    auto &subjectNode = findNode(getDesiredSubjectName(item), rootNode);
    if(ItsSubject(item))
        selectSubjectNode(subjectNode, select);
    else
    {
        QString desiredGroupName = item.text(0);
        selectGroupNode(findNode(desiredGroupName, subjectNode), select);
    }
}

bool QAsToLearnByUserChecker::isSelected(const QTreeWidgetItem &item)
{
    return item.data(2, Qt::CheckStateRole) == Qt::Checked;
}

bool QAsToLearnByUserChecker::ItsSubject(const QTreeWidgetItem &item) const
{
    return !item.parent();
}

QString QAsToLearnByUserChecker::getDesiredSubjectName(const QTreeWidgetItem &item)
{
    QString desiredSubjectName;
    if(ItsSubject(item))
    {
        desiredSubjectName = item.text(0);
    }
    else
    {
        desiredSubjectName = item.parent()->text(0);
    }
    return desiredSubjectName;
}

SimpleTree::Node<QA> & QAsToLearnByUserChecker::findNode(QString desiredName, SimpleTree::Node<QA> &rootNode)
{
    auto &nodes = rootNode.getNodes();
    auto foundNode = std::find_if(nodes.begin(), nodes.end(),
                 [&](const SimpleTree::Node<QA> &node){ return node.getName() == desiredName; });
    if(foundNode == nodes.end())
        throw std::logic_error("Question and answer repository corrupted");

    return *foundNode;
}

void QAsToLearnByUserChecker::selectGroupNode(SimpleTree::Node<QA>& groupNode, const bool select)
{
    groupNode.setInfo(NODE_INFO_ROLE_CHECKED, select);
    for(SimpleTree::Node<QA> &qaNode: groupNode.getNodes())
    {
        qaNode.setInfo(NODE_INFO_ROLE_CHECKED, select);
    }
    m_qARepository->onQAsUpdate();
}

void QAsToLearnByUserChecker::selectSubjectNode(SimpleTree::Node<QA> &subjectNode, const bool select)
{
    subjectNode.setInfo(NODE_INFO_ROLE_CHECKED, select);
    for(auto &groupNode: subjectNode.getNodes())
    {
        groupNode.setInfo(NODE_INFO_ROLE_CHECKED, select);
        for(SimpleTree::Node<QA> &qaNode: groupNode.getNodes())
        {
            qaNode.setInfo(NODE_INFO_ROLE_CHECKED, select);
        }
    }
    m_qARepository->onQAsUpdate();
}
