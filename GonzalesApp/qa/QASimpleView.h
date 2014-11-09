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
        qa(qa),
        presenter(presenter),
        dataObserver(p_observer)

    {
    }

    void markAsKnown() override
    {
        qa->markAsKnown(QDate::currentDate());
        dataObserver->onQAsUpdate();
    }
    void markAsUnknown() override
    {
        qa->markAsUnknown(QDate::currentDate());
        dataObserver->onQAsUpdate();
    }
    void presentQuestion() const override
    {
        qa->presentQuestion(*presenter);
    }
    void presentAnswer() const override
    {
        qa->presentAnswer(*presenter);
    }

private:
    std::shared_ptr<QA> qa;
    std::shared_ptr<IQAPresenter> presenter;
    std::shared_ptr<IQARepository> dataObserver;


};
