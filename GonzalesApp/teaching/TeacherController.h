#pragma once

#include "../uiobservers/IExceptionHandler.h"
#include "../qa/IQARepository.h"
#include "Teacher.h"
#include <memory>
#include <QObject>
#include "../qa/QAMarker.h"


class TeacherController: public QObject
{
    Q_OBJECT
public:
    TeacherController(std::shared_ptr<IQAsToLearnProvider> qARepository,
                      std::shared_ptr<IExceptionHandler> &exceptionHandler,
                      QObject *parent = 0):
        QObject(parent),
        m_qAsToLearnProvider(qARepository),
        m_exceptionHandler(exceptionHandler)
    {}

    void showCorrectAnswer();
    int questionsToLearnNum();
    void showNextQuestion();
    void markAsKnownAndShowNextQuestion();
    void markAsUnknownAndShowNextQuestion();
    void startTeaching();
    void registerQuestionAndAnswerPresenter(std::shared_ptr<IQuestionPresenter> questionProvider,
                                            std::shared_ptr<IAnswerPresenter> answerProvider);

private:
    std::shared_ptr<IQuestionPresenter> m_questionPresenter;
    std::shared_ptr<IAnswerPresenter> m_answerPresenter;
    std::shared_ptr<IQAsToLearnProvider> m_qAsToLearnProvider;
    std::unique_ptr<Teacher> m_teacher;
    std::shared_ptr<IExceptionHandler> m_exceptionHandler;
    std::shared_ptr<IQAMarker> m_qaMarker;
signals:
    void stopLearn();

};

