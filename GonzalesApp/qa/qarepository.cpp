#include "qarepository.h"



const SimpleTree::Node<QA> &QARepository::getQAs() const
{
    return m_questionsTree;
}

void QARepository::onQAsImport()
{
    m_questionsPresnter->presentQuestions(m_questionsTree);
    m_qAsSaver->save(m_questionsTree);
}

void QARepository::onQAsUpdate()
{
    m_qAsSaver->save(m_questionsTree);
}

QARepository::QARepository(const QString &userFilePath,
                           std::shared_ptr<IExceptionHandler> exceptionHandler,
                           std::shared_ptr<IQuestionCollectionPresenter> questionsPresenter,
                           std::shared_ptr<IQALoader> qAsLoader,
                           std::shared_ptr<IQASaver> qAsSaver):
    m_userQAsFilePath(userFilePath),
    m_exceptionHandler(exceptionHandler),
    m_questionsPresnter(questionsPresenter),
    m_qAsLoader(qAsLoader),
    m_qAsSaver(qAsSaver)
{
}

SimpleTree::Node<QA> &QARepository::getQAs()
{
    return m_questionsTree;
}

void QARepository::load()
{
    try
    {
        m_questionsTree = m_qAsLoader->load();
        m_questionsPresnter->presentQuestions(m_questionsTree);
    }
    catch(FileException &e)
    {
        m_exceptionHandler->handleException(e.what(), "Loader error");
    }
    catch(std::logic_error &e)
    {
        m_exceptionHandler->handleException(e.what(), "Loader error");
    }
}

void QARepository::registerQuestionCollectionPresenter(std::shared_ptr<IQuestionCollectionPresenter> presenter)
{
    m_questionsPresnter = presenter;
}
