#ifndef TEACHERADAPTER_H
#define TEACHERADAPTER_H

#include <QStringList>
#include <QMap>
#include <QDebug>
#include <QQueue>

#include "../teacher.h"

class TeacherQtAdapter
{
public:
    typedef QA QAPair;
    typedef std::deque< QAPair > QAQueue;

    TeacherQtAdapter(const QMap< QString, QString > QaMap)
    {
        QAQueue qAQueue;
        for(QMap< QString, QString >::const_iterator it = QaMap.begin(); it!=QaMap.end(); it++)
        {
            qDebug() << it.key() << it.value();
            qAQueue.push_back(QA(Question(it.key().toStdString()), Answer(it.value().toStdString())));
        }
        teacher.setQuestions(qAQueue);
    }
    void setQuestions(const QMap<QString, QString> QuestionAnswerMap){
        QAQueue qAQueue;
        for(QMap<QString, QString>::const_iterator it = QuestionAnswerMap.begin(); it!=QuestionAnswerMap.end(); it++)
        {
            qAQueue.push_back(QA(Question(it.key().toStdString()), Answer(it.value().toStdString())));
        }
        teacher.setQuestions(qAQueue);
    }

    void setQuestions(const QQueue<QA> questionAnswer){
        QAQueue qAQueue;
        foreach(QA item, questionAnswer)
        {
            qAQueue.push_back(item);
        }

        teacher.setQuestions(qAQueue);
    }

    bool checkAnswer(const QString &answer)
    {
        return teacher.checkAnswer(Answer(answer.toStdString()));
    }

    QString getNextQuestion()
    {
        return QString::fromStdString(teacher.getNextQuestion().geAstString());
    }

    QString getCorrectAnswer(const QString &question)
    {
        return QString::fromStdString(teacher.getCorrectAnswer(question.toStdString()).getAsString());
    }

    int questionsToLearnNum()
    {
        return teacher.questionsToLearnNum();
    }


private:
    Teacher teacher;

};

#endif // TEACHER_H
