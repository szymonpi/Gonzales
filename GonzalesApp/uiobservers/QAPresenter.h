#pragma once
#include <QTextEdit>
#include "IQAPresenter.h"

class QAPresenter : public IQAPresenter
{
public:
    QAPresenter(QTextEdit &textEditQuestion,
                QTextEdit &textEditAnswer):
        textEditQuestion(textEditQuestion),
        textEditAnswer(textEditAnswer)
    {}

    void presentQuestion(const QString &question)
    {
        textEditAnswer.clear();
        textEditAnswer.update();

        textEditQuestion.setText(question);
        textEditQuestion.setAlignment(Qt::AlignCenter); //todo move up!
        textEditQuestion.update();
    }

    void presentAnswer(const QString &answer)
    {
        textEditAnswer.setText(answer);
        textEditAnswer.setAlignment(Qt::AlignCenter); //todo move up!
        textEditAnswer.update();
    }

private:
    QTextEdit& textEditQuestion;
    QTextEdit& textEditAnswer;
};
