#include "answerpresenter.h"


AnswerPresenter::AnswerPresenter(QTextEdit &textEdit):
    m_textEdit(textEdit)
{

}

void AnswerPresenter::presentAnswer(const Answer &question)
{
    m_textEdit.setText(QString::fromStdString(question.getAsString()));
    m_textEdit.setAlignment(Qt::AlignCenter);
    m_textEdit.update();
}

void AnswerPresenter::clear()
{
    m_textEdit.clear();
    m_textEdit.update();
}
