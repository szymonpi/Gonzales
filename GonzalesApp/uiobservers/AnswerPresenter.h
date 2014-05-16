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
