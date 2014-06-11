#pragma once
#include "IQARepository.h"
#include "QALoader.h"
#include "QAImporter.h"
#include "QASaver.h"
#include <QMultiMap>
#include "../common/SimpleTree/Node.h"
#include "../uiobservers/IExceptionHandler.h"
#include "../uiobservers/IQuestionCollectionPresenter.h"
#include "IQASaver.h"


///@todo move load to loadhandler
///@todo move onQAsUpdate to apropriateUiObserver

class QARepository: public IQARepository
{
public:
    QARepository(std::shared_ptr<IExceptionHandler> exceptionHandler,
                 std::shared_ptr<IQALoader> qAsLoader,
                 std::shared_ptr<IQASaver> qAsSaver);

    SimpleTree::Node<QA> &getQAs();
    const SimpleTree::Node<QA> &getQAs() const;
    void onQAsImport();
    void onQAsUpdate();
    void load();
    void registerQuestionCollectionPresenter(std::shared_ptr<IQuestionCollectionPresenter> presenter);

private:
    SimpleTree::Node<QA> m_questionsTree;
    std::shared_ptr<IExceptionHandler> m_exceptionHandler;
    std::shared_ptr<IQuestionCollectionPresenter> m_questionsPresnter;
    std::shared_ptr<IQALoader> m_qAsLoader;
    std::shared_ptr<IQASaver> m_qAsSaver;
};
