#pragma once
#include "IAnswerPresenter.h"
#include <QTextEdit>

class AnswerPresenter : public IAnswerPresenter
{
public:
    AnswerPresenter(QTextEdit& textEdit);
    void presentAnswer(const Answer &question);
    void clear();

private:
    QTextEdit& m_textEdit;
};

class ITextAnswerPresenter
{
public:
    virtual void present(const QString &question) = 0;
    virtual void clear() = 0;
    virtual ~ITextAnswerPresenter(){}
};

class TextAnswerPresenter : public ITextAnswerPresenter
{
public:
    TextAnswerPresenter(QTextEdit &textEdit):
        m_textEdit(textEdit)
    {}

    void present(const QString &question)
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
