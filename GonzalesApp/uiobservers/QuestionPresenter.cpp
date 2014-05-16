#include "QuestionPresenter.h"


QuestionPresenter::QuestionPresenter(QTextEdit &textEdit):
    m_textEdit(textEdit)
{

}

void QuestionPresenter::presentQuestion(const Question &question)
{
    m_textEdit.setText(QString::fromStdString(question.getAsString()));
    m_textEdit.setAlignment(Qt::AlignCenter);
    m_textEdit.update();
}

void QuestionPresenter::clear()
{
    m_textEdit.clear();
    m_textEdit.update();
}
