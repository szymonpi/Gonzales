#include "QAsToLearnSelector.h"
#include "../Common/Common.h"


QAsToLearnSelector::QAsToLearnSelector(std::shared_ptr<IQARepository> qAsProvider):
    m_qARepository(qAsProvider)
{

}

bool QAsToLearnSelector::ItsSubject(const QTreeWidgetItem &item) const
{
    return !item.parent();
}

void QAsToLearnSelector::select(const QTreeWidgetItem &item)
{
    bool select = item.data(2, Qt::CheckStateRole) == Qt::Checked;
    if(item.childCount() == 0)
        return;

    SimpleTree::Node<QA> &rootNode = m_qARepository->getQAs();

    if(ItsSubject(item))
    {
        QString desiredSubjectName = item.text(0);
        for(auto &subjectNode: rootNode.getNodes())
        {
            if(desiredSubjectName == subjectNode.getName())
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
                return;
            }
            throw std::logic_error("Question and answer repository corrupted");
        }
    }
    else
    {
        QString desiredGroupName = item.text(0);
        QString desiredSubjectName = item.parent()->text(0);
        for(SimpleTree::Node<QA>& subjectNode: rootNode.getNodes())
        {
            if(desiredSubjectName == subjectNode.getName())
            {
                for(SimpleTree::Node<QA>& groupNode: subjectNode.getNodes())
                {
                    if (groupNode.getName() == desiredGroupName)
                    {
                        groupNode.setInfo(NODE_INFO_ROLE_CHECKED, select);
                            for(SimpleTree::Node<QA> &qaNode: groupNode.getNodes())
                            {
                                qaNode.setInfo(NODE_INFO_ROLE_CHECKED, select);
                            }
                        m_qARepository->onQAsUpdate();
                        return;
                    }
                    throw std::logic_error("Question and answer repository corrupted");
                }
            }
        }
    }
}
