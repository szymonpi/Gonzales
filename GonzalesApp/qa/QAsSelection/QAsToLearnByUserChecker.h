#pragma once
#include <QTreeWidget>
#include "../IQARepository.h"

class QAsToLearnByUserChecker
{
public:
    QAsToLearnByUserChecker(std::shared_ptr<IQARepository> qAsProvider);
    void select(const QTreeWidgetItem &item);

private:
    SimpleTree::Node<QA> & getRootNode();
    bool isSelected(const QTreeWidgetItem &item);
    bool ItsSubject(const QTreeWidgetItem &item) const;
    QString getDesiredSubjectName(const QTreeWidgetItem &item);
    void selectGroupNode(SimpleTree::Node<QA>& groupNode, const bool select);
    void selectSubjectNode(SimpleTree::Node<QA>& subjectNode, const bool select);
    SimpleTree::Node<QA> &findNode(QString desiredName, SimpleTree::Node<QA> &rootNode);
    void selectItem(const QTreeWidgetItem &item, SimpleTree::Node<QA> &rootNode, const bool select);

    std::shared_ptr<IQARepository> m_qARepository;
};

