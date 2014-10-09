#pragma once
#include "QAToViewConverter.h"
#include "IQARepository.h"
#include "QASimpleView.h"

class QAToSimpleViewConverter: public QAToViewConverter
{
public:
    QAToSimpleViewConverter(std::shared_ptr<IQAPresenter> qaPresenter,
                        std::shared_ptr<IQARepository> qaRepository):
        qaPresenter(qaPresenter),
        qaRepository(qaRepository)
    {

    }

    std::shared_ptr<QAView> convert(const std::shared_ptr<QA> &qaData) const override
    {
        return std::make_shared<QASimpleView>(qaPresenter,
                                              qaData,
                                              qaRepository);
    }
private:
    std::shared_ptr<IQAPresenter> qaPresenter;
    std::shared_ptr<IQARepository> qaRepository;

};
