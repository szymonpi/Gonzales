#ifndef TEACHERCONTROLLERFACTORY_H
#define TEACHERCONTROLLERFACTORY_H

#include <QTextEdit>
#include "teaching/teachercontroller.h"
#include "qa/QAsToLearnCheckedByUserProvider.h"

class TeacherControllerFactory{

public:
    TeacherControllerFactory(std::shared_ptr<QAsProvider> qasProvider,
                             QTextEdit &questionTextEdit,
                             QTextEdit &answerTextEdit):
        m_qasProvider(qasProvider),
        m_questionTextEdit(questionTextEdit),
        m_answerTextEdit(answerTextEdit)
    {

    }

    std::shared_ptr<TeacherController> create()
    {
        std::shared_ptr<IExceptionHandler> l_exceptionHandler = std::make_shared<ExceptionHandler>();
        std::shared_ptr<IQuestionPresenter> l_questionPresenter(new QuestionPresenter(m_questionTextEdit));
        std::shared_ptr<IAnswerPresenter> l_answerPresenter(new AnswerPresenter(m_answerTextEdit));
        std::shared_ptr<IQAsToLearnCheckedByUserProvider> l_qasCheckedByuserProvider(
                    std::make_shared<QAsToLearnCheckedByUserProvider>(m_qasProvider));
        std::shared_ptr<QAsToLearnProvider> qasToLearnProvider =
                std::make_shared<QAsToLearnProvider>(l_qasCheckedByuserProvider);

        return std::make_shared<TeacherController>(l_questionPresenter,
                                            l_answerPresenter,
                                            qasToLearnProvider,
                                            l_exceptionHandler);
    }

private:
    std::shared_ptr<QAsProvider> m_qasProvider;
    QTextEdit &m_questionTextEdit;
    QTextEdit &m_answerTextEdit;
};

#endif // TEACHERCONTROLLERFACTORY_H
