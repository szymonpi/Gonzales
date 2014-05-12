#ifndef QAREPOSITORY_H
#define QAREPOSITORY_H
#include "IQARepository.h"
#include "qaloader.h"
#include "qaimporter.h"
#include "qasaver.h"
#include <QMultiMap>
#include "../Common/SimpleTree/Node.h"
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
    QARepository(const QString &userFilePath,
                 std::shared_ptr<IExceptionHandler> exceptionHandler,
                 std::shared_ptr<IQuestionCollectionPresenter> questionsPresenter,
                 std::shared_ptr<IQALoader> qAsLoader);

    SimpleTree::Node<QA> &getQAs();
    const SimpleTree::Node<QA> &getQAs() const;
    void onQAsUpdate();
    void load();

private:
    SimpleTree::Node<QA> m_questionsTree;
    const QString m_userQAsFilePath;
    std::shared_ptr<IExceptionHandler> m_exceptionHandler;
    std::shared_ptr<IQuestionCollectionPresenter> m_questionsPresnter;
    std::shared_ptr<IQALoader> m_qAsLoader;
};

#endif // QAREPOSITORY_H
