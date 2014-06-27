#include "QuestionCollectionPresenter.h"
#include "../common/Common.h"

void QuestionCollectionPresenter::buildWidgetTree(const SimpleTree::Node<QA> &node, QTreeWidgetItem *parent)
{
    if(!node.getNodeValue().get())
    {
        QTreeWidgetItem *item = new QTreeWidgetItem(parent, TREE_WIDGET_TYPE_GROUP);
        item->setFlags(Qt::ItemIsUserCheckable);
        item->setData(2, Qt::CheckStateRole, node.getInfo(NODE_INFO_ROLE_CHECKED).toBool()?Qt::Checked:Qt::Unchecked);
        item->setText(0, node.getName());
        item->setDisabled(false);
        if(parent)
            parent->addChild(item);
        else
            m_widget.addTopLevelItem(item);
        foreach(const SimpleTree::Node<QA> &childNode, node.getNodes())
        {
            buildWidgetTree(childNode, item);
        }
    }
    else
    {
        QTreeWidgetItem *item = new QTreeWidgetItem(parent, TREE_WIDGET_TYPE_QA);
        item->setText(0, node.getNodeValue()->question.getAsString());
        item->setText(1, node.getNodeValue()->answer.getAsString());
        item->setDisabled(false);
        QPixmap pixmap("://resources/icons/question.jpg");
        QIcon icon(pixmap);
        item->setIcon(0, icon);
        if(parent)
            parent->addChild(item);
        else
            m_widget.addTopLevelItem(item);
    }
}

void QuestionCollectionPresenter::presentQuestions(const SimpleTree::Node<QA> &questions)
{
    m_widget.clear();
    foreach(const SimpleTree::Node<QA> &node, questions.getNodes())
    {
        buildWidgetTree(node, 0);
    }
}


QuestionCollectionPresenter::QuestionCollectionPresenter(QTreeWidget &treeWidget):
    m_widget(treeWidget)
{

}
