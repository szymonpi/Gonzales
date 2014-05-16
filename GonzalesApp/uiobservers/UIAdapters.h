#ifndef UIADAPTERS_H
#define UIADAPTERS_H
#include <QTextEdit>
#include <QTreeWidget>
#include <qa/qacontainer.h>
#include "qa/question.h"
#include "qa/answer.h"
#include "IUIAdapters.h"
#include <memory>
#include <QString>
#include "Common/common.h"

Q_DECLARE_METATYPE(std::weak_ptr<QA>);

// todo clear duplications - add class textpresenter inside questionpresenter and answerpresenter

class QuestionCollectionPresenter: public IQuestionCollectionPresenter
{
public:

    enum Type
    {
        TREE_WIDGET_TYPE_QA = 1,
        TREE_WIDGET_TYPE_GROUP = 2
    };


    QuestionCollectionPresenter(QTreeWidget &treeWidget):
        m_widget(treeWidget)
    {

    }

    void presentQuestions(const SimpleTree::Node<QA> &questions)
    {
        m_widget.clear();
        foreach(const SimpleTree::Node<QA> &node, questions.getNodes())
        {
            buildWidgetTree(node, 0);
        }
    }

    void buildWidgetTree(const SimpleTree::Node<QA> &node, QTreeWidgetItem *parent)
    {
        if(!node.getNodeValue().get())
        {
            QTreeWidgetItem *item = new QTreeWidgetItem(parent, TREE_WIDGET_TYPE_GROUP);
            item->setFlags(Qt::ItemIsUserCheckable);
            item->setData(2, Qt::CheckStateRole, Qt::Checked);
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
            std::weak_ptr<QA> weakPtr = node.getNodeValue();
            item->setText(0, QString::fromStdString(node.getNodeValue()->question.getAsString()));
            item->setText(1, QString::fromStdString(node.getNodeValue()->answer.getAsString()));
            item->setData(0, DATA_ROLE_QA_POINTER, QVariant::fromValue(weakPtr));
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

private:
    QTreeWidget &m_widget;
};

class QuestionPresenter : public IQuestionPresenter
{
public:
    QuestionPresenter(QTextEdit& textEdit):
        m_textEdit(textEdit)
    {

    }

    void presentQuestion(const Question &question)
    {
        m_textEdit.setText(QString::fromStdString(question.getAsString()));
        m_textEdit.setAlignment(Qt::AlignCenter);
        m_textEdit.update();
    }

    void clear()
    {
        m_textEdit.clear();
        m_textEdit.update();
    }

private:
    QTextEdit& m_textEdit;
};

class AnswerPresenter : public IAnswerPresenter
{
public:
    AnswerPresenter(QTextEdit& textEdit):
        m_textEdit(textEdit)
    {

    }

    void presentAnswer(const Answer &question)
    {
        m_textEdit.setText(QString::fromStdString(question.getAsString()));
        m_textEdit.setAlignment(Qt::AlignCenter);
        m_textEdit.update();
    }

    void clear()
    {
        m_textEdit.clear();
        m_textEdit.update();
    }

private:
    QTextEdit& m_textEdit;
};

#endif // UIADAPTERS_H
