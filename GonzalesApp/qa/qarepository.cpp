#include "qarepository.h"



const std::vector<SimpleTree::Node<QA> > &QARepository::getQAs() const
{
    return m_questionsTree;
}

void QARepository::onQAsUpdate()
{
    m_questionsPresnter->presentQuestions(m_questionsTree);
    QASaver saver;
    saver.save(m_questionsTree, m_userName);
}

std::vector<SimpleTree::Node<QA> > &QARepository::getQAs()
{
    return m_questionsTree;
}

void QARepository::load()
{
    QALoader loader;
    try
    {
        m_questionsTree = loader.load(m_userName);
        m_questionsPresnter->presentQuestions(m_questionsTree);
    }
    catch(FileException &e)
    {
        m_exceptionHandler->handleException(e.what(), "Loader error");
    }
}

//void QARepository::import(const QString &path)
//{
//    try
//    {
//        QAFromTextFileImporter importer;
//        std::vector<SimpleTree::Node<QA> > importedQuestions = importer.import(path);
//        if(importedQuestions.size() == 0)
//            return;
        
//        m_questionsTree.append(importedQuestions);

//        QASaver saver;
//        saver.save(m_questionsTree, m_userName);
//    }
//    catch(FileException &e)
//    {
//        m_exceptionHandler->handleException(e.what(), "Importer error");
//    }
//}
