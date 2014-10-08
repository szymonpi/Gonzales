#pragma once
#include "IQuestionPresenter.h"
#include <QTextEdit>

class QuestionPresenter : public IQuestionPresenter
{
public:
    QuestionPresenter(QTextEdit& textEdit);
    void presentQuestion(const Question &question);
    void clear();

private:
    QTextEdit& m_textEdit;
};

class ITextQuestionPresenter
{
public:
    virtual void present(const QString &question) = 0;
    virtual void clear() = 0;
    virtual ~ITextQuestionPresenter(){}
};

class TextQuestionPresenter : public ITextQuestionPresenter
{
public:
    TextQuestionPresenter(QTextEdit &textEdit):
        m_textEdit(textEdit)
    {}

    void presentQuestion(const QString &question)
    {
        m_textEdit.setText(question);
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
