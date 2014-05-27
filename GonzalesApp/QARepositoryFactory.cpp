#include "qarepositoryfactory.h"
#include "qa/QALoader.h"
#include "qa/QASaver.h"
#include "qa/QAsFilePathProvider.h"
#include <QTreeWidget>
#include "uiobservers/ExceptionHandler.h"
#include "uiobservers/QuestionCollectionPresenter.h"
#include "qa/qarepository.h"



QARepositoryFactory::QARepositoryFactory(std::shared_ptr<IQAsFilePathProvider> filePathProvider,
                                         std::shared_ptr<IQALoader> loader):
    m_qasFilePathProvider(filePathProvider),
    m_loader(loader)
{

}

std::shared_ptr<QARepository> QARepositoryFactory::create()
{
    std::shared_ptr<IExceptionHandler> l_exceptionHandler = std::make_shared<ExceptionHandler>();
    std::shared_ptr<QASaver> saver = std::make_shared<QASaver>(m_qasFilePathProvider);
    return std::make_shared<QARepository>(m_qasFilePathProvider->getPath(),
                                                  l_exceptionHandler,
                                                  m_loader,
                                                  saver);
}
