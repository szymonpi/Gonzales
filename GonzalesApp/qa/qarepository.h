#ifndef QAREPOSITORY_H
#define QAREPOSITORY_H
#include "iqarepository.h"
#include "qaloader.h"
#include "qaimporter.h"
#include "qasaver.h"
#include <QMultiMap>
#include "../Common/SimpleTree/node.h"
#include "../IExceptionHandler.h"
#include "../IUIAdapters.h"



//
//
//  QA REPOSITORY
//
//

//==================
//should be class that contains all QAs and trigger presentation of those QAs on every change.
//==================

class QARepository: public IQARepository
{
public:
    QARepository(const QString &userName,
                 std::shared_ptr<IExceptionHandler> exceptionHandler,
                 std::unique_ptr<IQuestionCollectionPresenter> questionsPresenter):
        m_userName(userName),
        m_exceptionHandler(exceptionHandler),
        m_questionsPresnter(std::move(questionsPresenter))
    {
    }

    std::vector<SimpleTree::Node<QA> > &getQAs();
    const std::vector<SimpleTree::Node<QA> > &getQAs() const;
    void onQAsUpdate();
    void load();

private:
    std::vector<SimpleTree::Node<QA>> m_questionsTree;
    const QString m_userName;
    std::shared_ptr<IExceptionHandler> m_exceptionHandler;
    std::unique_ptr<IQuestionCollectionPresenter> m_questionsPresnter;
};

#endif // QAREPOSITORY_H
