#ifndef TEACHERCONTROLLERFACTORY_H
#define TEACHERCONTROLLERFACTORY_H

#include <QTextEdit>
#include "teaching/teachercontroller.h"
#include "qa/QAsSelection/QAsToLearnCheckedByUserProvider.h"

class TeacherControllerFactory{

public:
    TeacherControllerFactory(std::shared_ptr<QAsProvider> qasProvider):
        m_qasProvider(qasProvider)
    {

    }

    std::shared_ptr<TeacherController> create()
    {
        std::shared_ptr<IExceptionHandler> l_exceptionHandler = std::make_shared<ExceptionHandler>();
        std::shared_ptr<IQAsToLearnCheckedByUserProvider> l_qasCheckedByuserProvider(
                    std::make_shared<QAsToLearnCheckedByUserProvider>(m_qasProvider));
        std::shared_ptr<QAsToLearnProvider> qasToLearnProvider =
                std::make_shared<QAsToLearnProvider>(l_qasCheckedByuserProvider);

        return std::make_shared<TeacherController>(qasToLearnProvider,
                                                   l_exceptionHandler);
    }

private:
    std::shared_ptr<QAsProvider> m_qasProvider;
};

#endif // TEACHERCONTROLLERFACTORY_H
