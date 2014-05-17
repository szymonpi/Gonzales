#pragma once
#include <QTreeWidget>
#include "QAsProvider.h"

class QAsToLearnSelector
{
public:
    QAsToLearnSelector(std::shared_ptr<QAsProvider> qAsProvider);

    void select(const QTreeWidgetItem &item);

private:
    void selectQAsForGroup(bool set, const QTreeWidgetItem &item, std::vector<SimpleTree::Node<QA>> subjectNodes);
    void selectQAsForSubject(bool set, std::vector<SimpleTree::Node<QA>> subjectNodes);
    std::vector<SimpleTree::Node<QA> > & getSubjects() const;
    std::vector<SimpleTree::Node<QA> > &getGroups(const QTreeWidgetItem &item) const;
    void selectQAs(std::vector<SimpleTree::Node<QA>> &nodes, bool set);

    std::shared_ptr<QAsProvider> m_qAsProvider;
    bool ItsSubject(const QTreeWidgetItem &item) const;
    QString getSubjectName(const QTreeWidgetItem &item) const;
};

