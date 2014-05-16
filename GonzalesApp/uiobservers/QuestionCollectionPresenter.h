#pragma once
#include "IQuestionCollectionPresenter.h"
#include <QTreeWidget>

class QuestionCollectionPresenter: public IQuestionCollectionPresenter
{
public:

    enum Type
    {
        TREE_WIDGET_TYPE_QA = 1,
        TREE_WIDGET_TYPE_GROUP = 2
    };

    QuestionCollectionPresenter(QTreeWidget &treeWidget);
    void presentQuestions(const SimpleTree::Node<QA> &questions);
    void buildWidgetTree(const SimpleTree::Node<QA> &node, QTreeWidgetItem *parent);

private:
    QTreeWidget &m_widget;
};
