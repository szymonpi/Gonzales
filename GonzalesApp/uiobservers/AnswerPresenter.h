#ifndef ANSWERPRESENTER_H
#define ANSWERPRESENTER_H
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

#endif // ANSWERPRESENTER_H
