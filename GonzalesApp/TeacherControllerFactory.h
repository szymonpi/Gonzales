#ifndef TEACHERCONTROLLERFACTORY_H
#define TEACHERCONTROLLERFACTORY_H

#include <QTextEdit>
#include "teaching/TeacherController.h"
#include "qa/QAsSelection/QAsToLearnCheckedByUserProvider.h"
#include "qa/QAsSelection/QAsSelector.h"
#include "qa/IQARepository.h"

class TeacherControllerFactory{

public:
    TeacherControllerFactory(std::shared_ptr<IQARepository> qasProvider):
        m_qasProvider(qasProvider)
    {

    }

    std::shared_ptr<TeacherController> create()
    {
        std::shared_ptr<IExceptionHandler> l_exceptionHandler = std::make_shared<ExceptionHandler>();
        std::shared_ptr<IQAsToLearnCheckedByUserProvider> l_qasCheckedByuserProvider(
                    std::make_shared<QAsToLearnCheckedByUserProvider>(m_qasProvider));
        std::shared_ptr<IQAsSelector> selector = std::make_shared<QAsSelector>(0.6, 10);
        std::shared_ptr<IQAMarker> qaMarker = std::make_shared<QAMarker>(m_qasProvider);
        std::shared_ptr<QAsToLearnProvider> qasToLearnProvider =
                std::make_shared<QAsToLearnProvider>(l_qasCheckedByuserProvider, selector);

        return std::make_shared<TeacherController>(qasToLearnProvider,
                                                   l_exceptionHandler,
                                                   qaMarker);
    }

private:
    std::shared_ptr<IQARepository> m_qasProvider;
};

#endif // TEACHERCONTROLLERFACTORY_H
