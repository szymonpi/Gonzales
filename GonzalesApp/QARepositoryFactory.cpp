#include "qarepositoryfactory.h"
#include "qa/QALoader.h"
#include "user/UserInfo.h"
#include <QTreeWidget>
#include "uiobservers/ExceptionHandler.h"
#include "uiobservers/QuestionCollectionPresenter.h"
#include "qa/qarepository.h"



QARepositoryFactory::QARepositoryFactory(QTreeWidget &widget,
                                         const QString &userName):
    m_widget(widget),
    m_userName(userName)
{

}

std::shared_ptr<QARepository> QARepositoryFactory::create()
{
    std::shared_ptr<IExceptionHandler> l_exceptionHandler = std::make_shared<ExceptionHandler>();
    PathCreator pathCreator;
    std::shared_ptr<IQuestionCollectionPresenter> l_questionCollectionPresenter(
                                new QuestionCollectionPresenter(m_widget));
    std::shared_ptr<QALoader> loader = std::make_shared<QALoader>();
    return std::make_shared<QARepository>(pathCreator.createQAsFilePath(m_userName),
                                                  l_exceptionHandler,
                                                  l_questionCollectionPresenter,
                                                  loader);
}
