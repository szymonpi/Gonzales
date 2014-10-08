#pragma once

#include <memory>

#include "QAView.h"
#include "../uiobservers/IQuestionPresenter.h"
#include "../uiobservers/IAnswerPresenter.h"
#include "IQARepository.h"

class QASimpleView: public QAView
{
public:
    QASimpleView(std::shared_ptr<IQuestionPresenter> questionPresenter,
                 std::shared_ptr<IAnswerPresenter> answerPresenter,
                 std::shared_ptr<QA> qa,
                 std::shared_ptr<IQARepository> p_observer):
        m_questionPresenter(questionPresenter),
        m_answerPresenter(answerPresenter),
        m_qaData(qa),
        m_observer(p_observer)

    {
    }

    void markAsKnown() override
    {
        auto qa = m_qaData.lock();
        qa->markAsKnown(QDate::currentDate());
        m_observer->onQAsUpdate();
    }
    void markAsUnknown() override
    {
        auto qa = m_qaData.lock();
        qa->markAsUnknown(QDate::currentDate());
        m_observer->onQAsUpdate();
    }
    void presentQuestion() const override
    {
        auto qa = m_qaData.lock();
        m_answerPresenter->clear();
        m_questionPresenter->presentQuestion(qa->question);
    }
    void presentAnswer() const override
    {
        auto qa = m_qaData.lock();
        m_answerPresenter->presentAnswer(qa->answer);
    }

private:
    std::shared_ptr<IQuestionPresenter> m_questionPresenter;
    std::shared_ptr<IAnswerPresenter> m_answerPresenter;
    std::weak_ptr<QA> m_qaData;
    std::shared_ptr<IQARepository> m_observer;


};
