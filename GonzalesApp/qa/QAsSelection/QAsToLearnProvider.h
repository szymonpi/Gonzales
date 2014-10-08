#pragma once

#include "../IQARepository.h"
#include "IQAsToLearnProvider.h"
#include "Selectors/IQAsSelector.h"
#include "IQAsToLearnCheckedByUserProvider.h"
#include "../QAToViewConverter.h"
#include <QQueue>
#include <memory>

class QAsToLearnProvider : public IQAsToLearnProvider
{
public:
    QAsToLearnProvider(std::shared_ptr<IQAsToLearnCheckedByUserProvider> qAsCheckedByUserProvider,
                       std::shared_ptr<IQAsSelector> qasSelector,
                       std::shared_ptr<QAToViewConverter> m_converter);
    QQueue<std::shared_ptr<QAView> > getQAs();

private:
    std::shared_ptr<IQAsToLearnCheckedByUserProvider> m_qAsCheckedByUserProvider;
    std::shared_ptr<IQAsSelector> m_selector;
    std::shared_ptr<QAToViewConverter> m_converter;
};
