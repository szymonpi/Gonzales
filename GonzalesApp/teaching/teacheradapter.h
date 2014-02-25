#ifndef TEACHERADAPTER_H
#define TEACHERADAPTER_H

#include <queue>
#include <QString>
#include "teacher.h"

#include <QQueue>
#include "teaching/iteacher.h"


class TeacherAdapter
{
public:

    TeacherAdapter(){}
    TeacherAdapter(const QQueue<QA> &questions){
        m_teacher.setQuestions(Teacher::QAQueue(questions.begin(), questions.end()));
    }

    void setQuestions(const QQueue<QA> &questions){

        m_teacher.setQuestions(Teacher::QAQueue(questions.begin(), questions.end()));
    }

    bool checkAnswer(const QString &answer)
    {
        return m_teacher.checkAnswer(Answer(answer.toStdString()));
    }

    QString getCorrectAnswer(const QString &question) const
    {
        return QString::fromStdString(m_teacher.getCorrectAnswer(Question(question.toStdString())).getAsString());
    }

    int questionsToLearnNum() const
    {
        return m_teacher.questionsToLearnNum();
    }

    QQueue<QA> getQAs() const
    {
        Teacher::QAQueue l_qAs = m_teacher.getQAs();
        QQueue<QA> l_qtQas;

        foreach (QA qa, l_qAs) {
            l_qtQas.append(qa);
        }

        return l_qtQas;
    }

    QString getNextQuestion()
    {
        return QString::fromStdString(m_teacher.getNextQuestion().getAsString());
    }

private:
    Teacher m_teacher;
};

#endif // TEACHERADAPTER_H
