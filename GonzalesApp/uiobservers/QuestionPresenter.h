#ifndef QUESTIONPRESENTER_H
#define QUESTIONPRESENTER_H
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

#endif // QUESTIONPRESENTER_H
