#include "importedqasappender.h"



void ImportedQAsAppender::append(std::vector<std::shared_ptr<QA> > importedQAs)
{
    std::vector<Node<QA> > &subjects = m_qAsRepository->getQAs();
    std::vector<Node<QA> > newNodes = createNewNodes(importedQAs);

    if(m_destinationSelector->select(createGroupsMap(subjects), createStringQuestionsList(importedQAs)))
    {
        appendNewNodes(newNodes, subjects);
        m_qAsRepository->onQAsUpdate();
    }
}

QStringList ImportedQAsAppender::createStringQuestionsList(std::vector<std::shared_ptr<QA> > &importedQAs)
{
    QStringList importedQuestionsList;
    foreach(const std::shared_ptr<QA> &qa, importedQAs)
    {
        importedQuestionsList.append(QString::fromStdString(qa->question.getAsString()));
    }

    return importedQuestionsList;
}

QStringList ImportedQAsAppender::createGroupList(std::vector<Node<QA> > &nodes)
{
    QStringList groupsList;
    for(unsigned i = 0; i < nodes.size(); ++i)
    {
        groupsList.append(nodes.at(i).getName());
    }

    return groupsList;
}

QMap<QString, QStringList> ImportedQAsAppender::createGroupsMap(std::vector<Node<QA> > &subjects)
{
    QMap<QString, QStringList> groupMap;
    for(auto subjectIt = subjects.begin(); subjectIt!= subjects.end(); ++subjectIt)
    {
        groupMap[(*subjectIt).getName()] = createGroupList((*subjectIt).getNodes());
    }
    return groupMap;
}

std::vector<Node<QA> > ImportedQAsAppender::createNewNodes(std::vector<std::shared_ptr<QA> > &importedQAs)
{
    std::vector<Node<QA> > newNodes;
    for(auto qaIt = importedQAs.begin(); qaIt!= importedQAs.end(); ++qaIt)
    {
        newNodes.push_back(Node<QA>(*qaIt));
    }

    return newNodes;
}

void ImportedQAsAppender::appendNewNodesToNewGroup(const QString &group,
                                                   std::vector<Node<QA> > &newNodes,
                                                   std::vector<Node<QA> > &groups)
{
    Node<QA> newGroup;
    newGroup.setName(group);
    newGroup.appendNodes(newNodes);
    groups.push_back(newGroup);
}

void ImportedQAsAppender::appendInExistingSubject(std::vector<Node<QA> > &groups,
                                                  std::vector<Node<QA> > &newNodes,
                                                  const QString &group)
{
    for(unsigned i = 0; i < groups.size(); i++)
    {
        if(groups.at(i).getName() == group)
        {
            groups.at(i).appendNodes(newNodes);
            return;
        }
    }
    appendNewNodesToNewGroup(group, newNodes, groups);
}

void ImportedQAsAppender::appendNewNodesToNewSubject(const QString &subject,
                                                     const QString &group,
                                                     std::vector<Node<QA> > &newNodes,
                                                     std::vector<Node<QA> > &subjects)
{
    Node<QA> groupN;
    groupN.setName(group);
    groupN.appendNodes(newNodes);
    Node<QA> subjectN;
    subjectN.setName(subject);
    subjectN.appendNode(groupN);
    subjects.push_back(subjectN);
}

void ImportedQAsAppender::appendNewNodesToRelevantSubject(const QString &subject,
                                                          const QString &group,
                                                          std::vector<Node<QA> > &newNodes,
                                                          std::vector<Node<QA> > &subjects)
{
    for(unsigned i=0; i < subjects.size(); ++i)
    {
        if(subjects.at(i).getName()==subject)
        {
            appendInExistingSubject(subjects[i].getNodes(), newNodes, group);
            return;
        }
    }
    appendNewNodesToNewSubject(subject, group, newNodes, subjects);
}

void ImportedQAsAppender::appendNewNodes(std::vector<Node<QA> > &newNodes,
                                         std::vector<Node<QA> > &subjects)
{
    QString subject = m_destinationSelector->getSubject();
    QString group = m_destinationSelector->getGroup();

    appendNewNodesToRelevantSubject(subject, group, newNodes, subjects);
}
