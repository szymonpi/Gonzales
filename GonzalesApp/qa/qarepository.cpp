#include "qarepository.h"



const SimpleTree::Node<QA> &QARepository::getQAs() const
{
    return m_questionsTree;
}

void QARepository::onQAsUpdate()
{
    m_questionsPresnter->presentQuestions(m_questionsTree);
    QASaver saver;
    saver.save(m_questionsTree, m_userQAsFilePath);
}

QARepository::QARepository(const QString &userFilePath,
                           std::shared_ptr<IExceptionHandler> exceptionHandler,
                           std::shared_ptr<IQuestionCollectionPresenter> questionsPresenter,
                           std::shared_ptr<IQALoader> qAsLoader):
    m_userQAsFilePath(userFilePath),
    m_exceptionHandler(exceptionHandler),
    m_questionsPresnter(questionsPresenter),
    m_qAsLoader(qAsLoader)
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
        m_questionsTree = m_qAsLoader->load(m_userQAsFilePath);
        m_questionsPresnter->presentQuestions(m_questionsTree);
    }
    catch(FileException &e)
    {
        m_exceptionHandler->handleException(e.what(), "Loader error");
    }
}
