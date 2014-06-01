#include "qarepositoryfactory.h"
#include "qa/QALoader.h"
#include "qa/QASaver.h"
#include "qa/QAsFilePathProvider.h"
#include <QTreeWidget>
#include "uiobservers/ExceptionHandler.h"
#include "uiobservers/QuestionCollectionPresenter.h"
#include "qa/qarepository.h"
#include "qa/QANullLoader.h"
#include "User/UserInfo.h"



std::shared_ptr<IQARepository> QARepositoryFactory::create(const UserInfo &userInfo)
{
    std::shared_ptr<QAsFilePathProvider> qasFilePathProvider = std::make_shared<QAsFilePathProvider>(userInfo);
    std::shared_ptr<IQALoader> loader;
    if(!qasFilePathProvider->isQAsFileExist())
    {
        qasFilePathProvider->createQAsFilePath();
        loader = std::make_shared<QANullLoader>();
    }
    else
    {
        loader = std::make_shared<QALoader>(qasFilePathProvider);
    }

    std::shared_ptr<IExceptionHandler> l_exceptionHandler = std::make_shared<ExceptionHandler>();
    std::shared_ptr<QASaver> saver = std::make_shared<QASaver>(qasFilePathProvider);
    return std::make_shared<QARepository>(l_exceptionHandler,
                                                  loader,
                                                  saver);
}
