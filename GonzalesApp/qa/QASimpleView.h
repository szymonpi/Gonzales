#pragma once

#include <memory>

#include "QAView.h"
#include "../uiobservers/IQAPresenter.h"
#include "IQARepository.h"

class QASimpleView: public QAView
{
public:
    QASimpleView(std::shared_ptr<IQAPresenter> presenter,
                 std::shared_ptr<QA> qa,
                 std::shared_ptr<IQARepository> p_observer):
        m_presenter(presenter),
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
        m_presenter->presentQuestion(qa->question);
    }
    void presentAnswer() const override
    {
        auto qa = m_qaData.lock();
        m_presenter->presentAnswer(qa->answer);
    }

private:
    std::shared_ptr<IQAPresenter> m_presenter;
    std::weak_ptr<QA> m_qaData;
    std::shared_ptr<IQARepository> m_observer;


};
