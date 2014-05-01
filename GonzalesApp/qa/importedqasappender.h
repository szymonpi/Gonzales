#ifndef IMPORTEDQASAPPENDER_H
#define IMPORTEDQASAPPENDER_H
#include "../Common/simpletree.h"
#include "../qa/qacontainer.h"
#include "QAsAppender.h"
#include <QStringList>
#include "iqarepository.h"
#include <QMap>
#include <QPair>
#include <QStringList>
#include "../QAsDestinationSelector.h"


class ImportedQAsAppender: public QAsAppender
{
public:
    ImportedQAsAppender(std::shared_ptr<QAsDestinationSelector> destinationSelector,
                        std::shared_ptr<IQARepository> qAsRepository):
        m_destinationSelector(destinationSelector),
        m_qAsRepository(qAsRepository)
    {

    }

    void append(std::vector<std::shared_ptr<QA> > importedQAs);

private:
    void appendNewNodesToNewSubject(const QString &subject,
                                    const QString &group,
                                    std::vector<Node<QA> > &newNodes,
                                    std::vector<Node<QA> > &subjects);
    void appendNewNodesToNewGroup(const QString &group,
                                  std::vector<Node<QA> > &newNodes,
                                  std::vector<Node<QA> > &groups);

    void appendInExistingSubject(std::vector<Node<QA> > &groups,
                                 std::vector<Node<QA> > &newNodes,
                                 const QString &group);
    void appendNewNodesToRelevantSubject(const QString &subject,
                                         const QString &group,
                                         std::vector<Node<QA> > &newNodes,
                                         std::vector<Node<QA> > &subjects);
    QStringList createStringQuestionsList(std::vector<std::shared_ptr<QA> > &importedQAs);
    QStringList createGroupList(std::vector<Node<QA>> &nodes);
    QMap<QString, QStringList> createGroupsMap(std::vector<Node<QA> > &subjects);
    std::vector<Node<QA> > createNewNodes(std::vector<std::shared_ptr<QA> > &importedQAs);
    void appendNewNodes(std::vector<Node<QA> > &newNodes, std::vector<Node<QA> > &subjects);

    std::shared_ptr<QAsDestinationSelector> m_destinationSelector;
    std::shared_ptr<IQARepository> m_qAsRepository;
};

#endif // IMPORTEDQASAPPENDER_H
