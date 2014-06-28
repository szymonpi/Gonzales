#include "TeacherController.h"

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
    if(m_teacher->questionsToLearnNum() <= 0)
    {
        emit stopLearn();
        return;
    }
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
    try
    {
        m_teacher.reset(new Teacher(m_qAsToLearnProvider));
    }
    catch(std::logic_error &e)
    {
        m_exceptionHandler->handleException(e.what(), "Teacher error");
        return;
    }

    if(m_teacher->questionsToLearnNum()==0)
    {
        m_exceptionHandler->handleException("You has just finished learning, there is no Question left", "Info");
        return;
    }
    showNextQuestion();
}
