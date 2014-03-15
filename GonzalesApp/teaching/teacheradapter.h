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

    TeacherAdapter(std::shared_ptr<ITextPresenter> questionPresenter,
                   std::shared_ptr<ITextPresenter> answerPresenter):
        m_teacher(questionPresenter, answerPresenter){}

    TeacherAdapter(const QQueue<QA> &questions, std::shared_ptr<ITextPresenter> questionPresenter,
                   std::shared_ptr<ITextPresenter> answerPresenter):
        m_teacher(questionPresenter, answerPresenter)
    {
        m_teacher.setQuestions(Teacher::QAQueue(questions.begin(), questions.end()));
    }

    void setQuestions(const QQueue<QA> &questions){

        m_teacher.setQuestions(Teacher::QAQueue(questions.begin(), questions.end()));
    }


    void showCorrectAnswer() const
    {
        m_teacher.showCorrectAnswer();
    }

    int questionsToLearnNum() const
    {
        return m_teacher.questionsToLearnNum();
    }

    void showNextQuestion()
    {
         m_teacher.showNextQuestion();
    }

    void markAsKnown()
    {
        m_teacher.markAsKnown();
    }

    void markAsUnknown()
    {
        m_teacher.markAsUnknown();
    }

private:
    Teacher m_teacher;
};

#endif // TEACHERADAPTER_H
