#ifndef TEACHERCONTROLLERFACTORY_H
#define TEACHERCONTROLLERFACTORY_H

#include <QTextEdit>
#include "teaching/TeacherController.h"
#include "qa/QAsSelection/QAsToLearnCheckedByUserProvider.h"
#include "qa/QAsSelection/Selectors/QAsSelector.h"
#include "qa/QAsSelection/Selectors/QAsNewSelector.h"
#include "qa/QAsSelection/Selectors/QAsForRepeatSelector.h"
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

    std::shared_ptr<TeacherController> create(std::shared_ptr<IQuestionPresenter> questionProvider,
                                              std::shared_ptr<IAnswerPresenter> answerProvider)
    {
        std::shared_ptr<IExceptionHandler> exceptionHandler = std::make_shared<ExceptionHandler>();
        std::shared_ptr<IQAsToLearnCheckedByUserProvider> qasCheckedByUserProvider(
                    std::make_shared<QAsToLearnCheckedByUserProvider>(qasProvider));
        auto qaToViewConverter = std::make_shared<QAToSimpleViewConverter>(questionProvider,
                                                                           answerProvider,
                                                                           qasProvider);
        std::set<Day> periods{1,2,7,30,60,180,360};
        auto repeatPeriodChecker = std::make_shared<QARepeatPeriodChecker>(periods);
        auto forRepeatSelector = std::make_shared<QAsForRepeatSelector>(repeatPeriodChecker);
        auto notLearnedSelector = std::make_shared<QAsNotLearnedSelector>();
        auto newSelector = std::make_shared<QAsNewSelector>();

        std::vector<std::shared_ptr<IQAsSelector> > selectors;
        selectors.push_back(forRepeatSelector);
        selectors.push_back(notLearnedSelector);
        selectors.push_back(newSelector);

        std::shared_ptr<IQAsSelector> selector = std::make_shared<QAsSelector>(selectors);
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
