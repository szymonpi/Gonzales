#include "teachercontroller.h"

void TeacherController::showCorrectAnswer()
{
    try
    {
        m_teacher->showCorrectAnswer();
    }
    catch(std::logic_error &e)
    {
        m_exceptionHandler->handleException(e.what(), "Teacher error");
    }
}

int TeacherController::questionsToLearnNum()
{
    return m_teacher->questionsToLearnNum();
}

void TeacherController::showNextQuestion()
{
    try
    {
        m_teacher->showNextQuestion();
    }
    catch(std::logic_error &e)
    {
        m_exceptionHandler->handleException(e.what(), "Teacher error");
    }
}

void TeacherController::markAsKnownAndShowNextQuestion()
{
    m_teacher->markAsKnown();
    showNextQuestion();
}

void TeacherController::markAsUnknownAndShowNextQuestion()
{
    m_teacher->markAsUnknown();
    showNextQuestion();
}

void TeacherController::startTeaching()
{
    m_teacher.reset(new Teacher(m_questionPresenter, m_answerPresenter, m_qARepository));
    if(m_teacher->questionsToLearnNum()==0)
        return;
    showNextQuestion();
}
