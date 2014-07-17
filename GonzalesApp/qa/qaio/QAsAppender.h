#pragma once
#include "../../common/SimpleTree/Node.h"
#include "../QA.h"
#include "IQAsAppender.h"
#include <QStringList>
#include "../IQARepository.h"
#include <QMap>
#include <QPair>
#include <QStringList>
#include "../../uiobservers/QAsDestinationSelector.h"


class QAsAppender: public IQAsAppender
{
public:
    QAsAppender(std::shared_ptr<QAsDestinationSelector> destinationSelector,
                        std::shared_ptr<IQARepository> qAsRepository):
        m_destinationSelector(destinationSelector),
        m_qAsRepository(qAsRepository)
    {

    }

    void append(std::vector<std::shared_ptr<QA> > importedQAs);

private:
    void appendNewNodesToNewSubject(const QString &subject,
                                    const QString &group,
                                    std::vector<SimpleTree::Node<QA> > &newNodes,
                                    SimpleTree::Node<QA> &subjects);
    void appendNewNodesToNewGroup(const QString &group,
                                  std::vector<SimpleTree::Node<QA> > &newNodes,
                                  std::vector<SimpleTree::Node<QA> > &groups);

    void appendInExistingSubject(std::vector<SimpleTree::Node<QA> > &groups,
                                 std::vector<SimpleTree::Node<QA> > &newNodes,
                                 const QString &group);
    void appendNewNodesToRelevantSubject(const QString &subject,
                                         const QString &group,
                                         std::vector<SimpleTree::Node<QA>> &newNodes,
                                         SimpleTree::Node<QA> &mainNode);
    QStringList createStringQuestionsList(std::vector<std::shared_ptr<QA>> &importedQAs);
    QStringList createGroupList(std::vector<SimpleTree::Node<QA>> &nodes);
    QMap<QString, QStringList> createGroupsMap(SimpleTree::Node<QA> &subjects);
    std::vector<SimpleTree::Node<QA> > createNewNodes(std::vector<std::shared_ptr<QA>> &importedQAs);
    void appendNewNodes(std::vector<SimpleTree::Node<QA> > &newNodes, SimpleTree::Node<QA> &mainNode);

    std::shared_ptr<QAsDestinationSelector> m_destinationSelector;
    std::shared_ptr<IQARepository> m_qAsRepository;
};
