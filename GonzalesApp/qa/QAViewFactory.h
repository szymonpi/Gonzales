#pragma once
#include "QASimpleView.h"
#include <memory>


class QAViewFactory
{
public:
    ~QAViewFactory(){}
    virtual std::shared_ptr<QAView> createQAView(const std::shared_ptr<QA> qaData) const = 0;
};

class QASimpleViewFactory: public QAViewFactory
{
public:
    QASimpleViewFactory(std::shared_ptr<IQuestionPresenter> questionPresenter,
                        std::shared_ptr<IAnswerPresenter> answerPresenter,
                        std::shared_ptr<IQAMarker> qaMarker):
        m_questionPresenter(questionPresenter),
        m_answerPresenter(answerPresenter),
        m_qaMarker(qaMarker)
    {

    }

    std::shared_ptr<QAView> createQAView(const std::shared_ptr<QA> qaData) const override
    {
        return std::make_shared<QASimpleView>(m_questionPresenter, m_answerPresenter, m_qaMarker, qaData);
    }
private:
    std::shared_ptr<IQuestionPresenter> m_questionPresenter;
    std::shared_ptr<IAnswerPresenter> m_answerPresenter;
    std::shared_ptr<IQAMarker> m_qaMarker;

};
