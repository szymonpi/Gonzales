#ifndef TEACHERCONTROLLERFACTORY_H
#define TEACHERCONTROLLERFACTORY_H

#include <QTextEdit>
#include "teaching/TeacherController.h"
#include "qa/QAsSelection/QAsToLearnCheckedByUserProvider.h"
#include "qa/QAsSelection/Selectors/QAsSelector.h"
#include "qa/QAsSelection/Selectors/QAsNewSelector.h"
#include "qa/QAsSelection/Selectors/QAsNotLearnedSelector.h"
#include "qa/QAsSelection/Selectors/Utils/QARepeatPeriodChecker.h"
#include "qa/IQARepository.h"
#include "uiobservers/ExceptionHandler.h"
#include "qa/QAToSimpleViewConverter.h"

class TeacherControllerFactory{

public:
    TeacherControllerFactory(std::shared_ptr<IQARepository> qasProvider):
        qasProvider(qasProvider)
    {

    }

    std::shared_ptr<TeacherController> create(std::shared_ptr<IQAPresenter> qaPresenter)
    {
        std::shared_ptr<IExceptionHandler> exceptionHandler = std::make_shared<ExceptionHandler>();
        std::shared_ptr<IQAsToLearnCheckedByUserProvider> qasCheckedByUserProvider(
                    std::make_shared<QAsToLearnCheckedByUserProvider>(qasProvider));
        auto qaToViewConverter = std::make_shared<QAToSimpleViewConverter>(qaPresenter,
                                                                           qasProvider);

        std::shared_ptr<IQAsSelector> selector = std::make_shared<QAsSelector>();
        std::shared_ptr<QAsToLearnProvider> qasToLearnProvider =
                std::make_shared<QAsToLearnProvider>(qasCheckedByUserProvider,
                                                     selector,
                                                     qaToViewConverter);

        return std::make_shared<TeacherController>(qasToLearnProvider,
                                                   exceptionHandler);
    }

private:
    std::shared_ptr<IQARepository> qasProvider;
};

#endif // TEACHERCONTROLLERFACTORY_H
