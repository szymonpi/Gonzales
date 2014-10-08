#pragma once
#include "QAToViewConverter.h"
#include "../uiobservers/IQuestionPresenter.h"
#include "../uiobservers/IAnswerPresenter.h"
#include "IQARepository.h"
#include "QASimpleView.h"

class QAToSimpleViewConverter: public QAToViewConverter
{
public:
    QAToSimpleViewConverter(std::shared_ptr<IQuestionPresenter> questionPresenter,
                        std::shared_ptr<IAnswerPresenter> answerPresenter,
                        std::shared_ptr<IQARepository> qaRepository):
        m_questionPresenter(questionPresenter),
        m_answerPresenter(answerPresenter),
        qaRepository(qaRepository)
    {

    }

    std::shared_ptr<QAView> convert(const std::shared_ptr<QA> &qaData) const override
    {
        return std::make_shared<QASimpleView>(m_questionPresenter,
                                              m_answerPresenter,
                                              qaData,
                                              qaRepository);
    }
private:
    std::shared_ptr<IQuestionPresenter> m_questionPresenter;
    std::shared_ptr<IAnswerPresenter> m_answerPresenter;
    std::shared_ptr<IQARepository> qaRepository;

};
