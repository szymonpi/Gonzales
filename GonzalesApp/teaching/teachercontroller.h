#ifndef TEACHERCONTROLLER_H
#define TEACHERCONTROLLER_H

#include "../uiobservers/IExceptionHandler.h"
#include "../qa/IQARepository.h"
#include "teacher.h"
#include <memory>

class TeacherController
{
public:
    TeacherController(std::shared_ptr<IQuestionPresenter> questionPresenter,
                      std::shared_ptr<IAnswerPresenter> answerPresenter,
                      std::shared_ptr<IQAsToLearnProvider> qARepository,
                      std::shared_ptr<IExceptionHandler> &exceptionHandler):
        m_questionPresenter(std::move(questionPresenter)),
        m_answerPresenter(std::move(answerPresenter)),
        m_qAsToLearnProvider(qARepository),
        m_exceptionHandler(exceptionHandler)
    {}

    void showCorrectAnswer();
    int questionsToLearnNum();
    void showNextQuestion();
    void markAsKnownAndShowNextQuestion();
    void markAsUnknownAndShowNextQuestion();
    void startTeaching();

private:
    std::shared_ptr<IQuestionPresenter> m_questionPresenter; //change to factory and then to unique_ptr
    std::shared_ptr<IAnswerPresenter> m_answerPresenter; //change to factory and then to unique ptr
    std::shared_ptr<IQAsToLearnProvider> m_qAsToLearnProvider;
    std::unique_ptr<Teacher> m_teacher;
    std::shared_ptr<IExceptionHandler> m_exceptionHandler;

};

#endif // TEACHERCONTROLLER_H
