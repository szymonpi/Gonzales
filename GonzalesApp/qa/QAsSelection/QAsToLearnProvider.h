#pragma once

#include "../IQARepository.h"
#include "IQAsToLearnProvider.h"
#include "IQAsSelector.h"
#include "IQAsToLearnCheckedByUserProvider.h"
#include "../QAViewFactory.h"
#include <QQueue>
#include <memory>

class QAsToLearnProvider : public IQAsToLearnProvider
{
public:
    QAsToLearnProvider(std::shared_ptr<IQAsToLearnCheckedByUserProvider> qAsCheckedByUserProvider,
                       std::shared_ptr<IQAsSelector> qasSelector,
                       std::shared_ptr<QAViewFactory> qaViewFactory);
    QQueue<std::shared_ptr<QAView> > getQAs();

private:
    std::shared_ptr<IQAsToLearnCheckedByUserProvider> m_qAsCheckedByUserProvider;
    std::shared_ptr<IQAsSelector> m_selector;
    std::shared_ptr<QAViewFactory> m_qaViewFactory;
};
