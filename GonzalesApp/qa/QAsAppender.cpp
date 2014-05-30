#include "QAsAppender.h"



void QAsAppender::append(std::vector<std::shared_ptr<QA> > importedQAs)
{
    SimpleTree::Node<QA> &mainNode = m_qAsRepository->getQAs();
    std::vector<SimpleTree::Node<QA> > newNodes = createNewNodes(importedQAs);

    if(m_destinationSelector->select(createGroupsMap(mainNode), createStringQuestionsList(importedQAs)))
    {
        appendNewNodes(newNodes, mainNode);
        m_qAsRepository->onQAsImport();
    }
}

QStringList QAsAppender::createStringQuestionsList(std::vector<std::shared_ptr<QA> > &importedQAs)
{
    QStringList importedQuestionsList;
    foreach(const std::shared_ptr<QA> &qa, importedQAs)
    {
        importedQuestionsList.append((qa->getQuestion().getAsString()));
    }

    return importedQuestionsList;
}

QStringList QAsAppender::createGroupList(std::vector<SimpleTree::Node<QA> > &nodes)
{
    QStringList groupsList;
    for(unsigned i = 0; i < nodes.size(); ++i)
    {
        groupsList.append(nodes.at(i).getName());
    }

    return groupsList;
}

QMap<QString, QStringList> QAsAppender::createGroupsMap(SimpleTree::Node<QA> &qas)
{
    std::vector<SimpleTree::Node<QA>> &subjects = qas.getNodes();
    QMap<QString, QStringList> groupMap;
    for(auto subjectIt = subjects.begin(); subjectIt!= subjects.end(); ++subjectIt)
    {
        groupMap[(*subjectIt).getName()] = createGroupList((*subjectIt).getNodes());
    }
    return groupMap;
}

std::vector<SimpleTree::Node<QA> > QAsAppender::createNewNodes(std::vector<std::shared_ptr<QA> > &importedQAs)
{
    std::vector<SimpleTree::Node<QA> > newNodes;
    for(auto qaIt = importedQAs.begin(); qaIt!= importedQAs.end(); ++qaIt)
    {
        newNodes.push_back(SimpleTree::Node<QA>(*qaIt));
    }

    return newNodes;
}

void QAsAppender::appendNewNodesToNewGroup(const QString &group,
                                                   std::vector<SimpleTree::Node<QA> > &newNodes,
                                                   std::vector<SimpleTree::Node<QA> > &groups)
{
    SimpleTree::Node<QA> newGroup;
    newGroup.setName(group);
    newGroup.appendNodes(newNodes);
    groups.push_back(newGroup);
}

void QAsAppender::appendInExistingSubject(std::vector<SimpleTree::Node<QA> > &groups,
                                                  std::vector<SimpleTree::Node<QA> > &newNodes,
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

void QAsAppender::appendNewNodesToNewSubject(const QString &subject,
                                                     const QString &group,
                                                     std::vector<SimpleTree::Node<QA> > &newNodes,
                                                     SimpleTree::Node<QA> &mainNode)
{
    SimpleTree::Node<QA> groupN;
    groupN.setName(group);
    groupN.appendNodes(newNodes);
    SimpleTree::Node<QA> subjectN;
    subjectN.setName(subject);
    subjectN.appendNode(groupN);
    mainNode.appendNode(subjectN);
}

void QAsAppender::appendNewNodesToRelevantSubject(const QString &subject,
                                                          const QString &group,
                                                          std::vector<SimpleTree::Node<QA> > &newNodes,
                                                          SimpleTree::Node<QA> &mainNode)
{
    for(unsigned i=0; i < mainNode.size(); ++i)
    {
        if(mainNode.getNode(i).getName()==subject)
        {
            appendInExistingSubject(mainNode.getNode(i).getNodes(), newNodes, group);
            return;
        }
    }
    appendNewNodesToNewSubject(subject, group, newNodes, mainNode);
}

void QAsAppender::appendNewNodes(std::vector<SimpleTree::Node<QA> > &newNodes,
                                         SimpleTree::Node<QA> &mainNode)
{
    QString subject = m_destinationSelector->getSubject();
    QString group = m_destinationSelector->getGroup();

    appendNewNodesToRelevantSubject(subject, group, newNodes, mainNode);
}
