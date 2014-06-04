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
        m_teacher.reset(new Teacher(m_questionPresenter, m_answerPresenter, m_qAsToLearnProvider));
    }
    catch(std::logic_error &e)
    {
        m_exceptionHandler->handleException(e.what(), "Teacher error");
        return;
    }

    if(m_teacher->questionsToLearnNum()==0)
    {
        m_exceptionHandler->handleException("You finished learning, there is no items left", "Info");
        return;
    }
    showNextQuestion();
}

void TeacherController::registerQuestionAndAnswerPresenter(std::shared_ptr<IQuestionPresenter> questionProvider,
                                                           std::shared_ptr<IAnswerPresenter> answerProvider)
{
    m_questionPresenter = questionProvider;
    m_answerPresenter = answerProvider;
}
