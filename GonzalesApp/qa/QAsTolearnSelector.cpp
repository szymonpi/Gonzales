#include "QAsToLearnSelector.h"



QAsToLearnSelector::QAsToLearnSelector(std::shared_ptr<QAsProvider> qAsProvider):
    m_qAsProvider(qAsProvider)
{

}

void QAsToLearnSelector::selectQAs(std::vector<SimpleTree::Node<QA>> &nodes, bool set)
{
    for(auto it = nodes.begin(); it!= nodes.end(); ++it)
    {
        SimpleTree::Node<QA> node = *it;
        node.getNodeValue()->m_toLearn = set;
    }
}

std::vector<SimpleTree::Node<QA> > & QAsToLearnSelector::getSubjects() const
{
    SimpleTree::Node<QA> &rootNode = m_qAsProvider->getQAs();
    std::vector<SimpleTree::Node<QA>> &nodes = rootNode.getNodes();

    return nodes;
}

std::vector<SimpleTree::Node<QA>>& QAsToLearnSelector::getGroups(const QTreeWidgetItem &item) const
{
    QString subjectName = getSubjectName(item);
    std::vector<SimpleTree::Node<QA>> &subjects = getSubjects();
    for(auto it = subjects.begin(); it!= subjects.end(); ++it)
    {
        SimpleTree::Node<QA> &node = *it;
        if(node.getName() == subjectName)
        {
            return node.getNodes();
        }
    }
    throw std::logic_error("Repository corrupted");
}

bool QAsToLearnSelector::ItsSubject(const QTreeWidgetItem &item) const
{
    return !item.parent();
}

QString QAsToLearnSelector::getSubjectName(const QTreeWidgetItem &item) const
{
    if(ItsSubject(item))
    {
        return item.text(0);
    }

    return item.parent()->text(0);
}

void QAsToLearnSelector::selectQAsForGroup(bool set, const QTreeWidgetItem &item, std::vector<SimpleTree::Node<QA> > subjectNodes)
{
    QString group = item.text(0);
    for(auto it = subjectNodes.begin(); it!= subjectNodes.end(); ++it)
    {
        SimpleTree::Node<QA> groupNode = *it;
        if(groupNode.getName()==group)
        {
            std::vector<SimpleTree::Node<QA>> &nodes = groupNode.getNodes();
            selectQAs(nodes, set);
        }
    }
}

void QAsToLearnSelector::selectQAsForSubject(bool set, std::vector<SimpleTree::Node<QA>> subjectNodes)
{
    for(auto it = subjectNodes.begin(); it!= subjectNodes.end(); ++it)
    {
        std::vector<SimpleTree::Node<QA>> &QAs = (*it).getNodes();
        selectQAs(QAs, set);
    }
}

void QAsToLearnSelector::select(const QTreeWidgetItem &item)
{
    bool set = item.data(2, Qt::CheckStateRole) == Qt::Checked;
    if(item.childCount() == 0)
        return;

    if(ItsSubject(item))
        selectQAsForSubject(set, getGroups(item));
    else
        selectQAsForGroup(set, item, getGroups(item));
}
