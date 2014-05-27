#pragma once
#include "IQARepository.h"
#include "qaloader.h"
#include "qaimporter.h"
#include "qasaver.h"
#include <QMultiMap>
#include "../Common/SimpleTree/Node.h"
#include "../uiobservers/IExceptionHandler.h"
#include "../uiobservers/IQuestionCollectionPresenter.h"
#include "IQASaver.h"


///@todo move load to loadhandler
///@todo move onQAsUpdate to apropriateUiObserver

class QARepository: public IQARepository
{
public:
    QARepository(const QString &userFilePath,
                 std::shared_ptr<IExceptionHandler> exceptionHandler,
                 std::shared_ptr<IQALoader> qAsLoader,
                 std::shared_ptr<IQASaver> qAsSaver,
                 std::shared_ptr<IQuestionCollectionPresenter> questionCollectionPresenter = std::shared_ptr<IQuestionCollectionPresenter>());

    SimpleTree::Node<QA> &getQAs();
    const SimpleTree::Node<QA> &getQAs() const;
    void onQAsImport();
    void onQAsUpdate();
    void load();
    void registerQuestionCollectionPresenter(std::shared_ptr<IQuestionCollectionPresenter> presenter);

private:
    SimpleTree::Node<QA> m_questionsTree;
    const QString m_userQAsFilePath;
    std::shared_ptr<IExceptionHandler> m_exceptionHandler;
    std::shared_ptr<IQuestionCollectionPresenter> m_questionsPresnter;
    std::shared_ptr<IQALoader> m_qAsLoader;
    std::shared_ptr<IQASaver> m_qAsSaver;
};
