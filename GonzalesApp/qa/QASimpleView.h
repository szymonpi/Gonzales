#pragma once

#include <memory>

#include "QAView.h"
#include "../uiobservers/IQuestionPresenter.h"
#include "../uiobservers/IAnswerPresenter.h"
#include "QAMarker.h"

class QASimpleView: public QAView
{
public:
    QASimpleView(std::shared_ptr<IQuestionPresenter> questionPresenter,
                 std::shared_ptr<IAnswerPresenter> answerPresenter,
                 std::shared_ptr<IQAMarker> qaMarker,
                 std::shared_ptr<QA> qa):
        m_questionPresenter(questionPresenter),
        m_answerPresenter(answerPresenter),
        m_qaMarker(qaMarker),
        m_qaData(qa)

    {

    }

    void markAsKnown() override
    {
        auto qa = m_qaData.lock();
        m_qaMarker->markAsKnown(*qa);
    }
    void markAsUnknown() override
    {
        auto qa = m_qaData.lock();
        m_qaMarker->markAsUnknown(*qa);
    }
    void presentQuestion() const override
    {
        auto qa = m_qaData.lock();
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
    std::shared_ptr<IQAMarker> m_qaMarker;
    std::weak_ptr<QA> m_qaData;

};
