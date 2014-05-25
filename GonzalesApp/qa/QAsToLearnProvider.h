#pragma once

#include "IQARepository.h"
#include "IQAsToLearnProvider.h"
#include "IQAsToLearnCheckedByUserProvider.h"
#include <QQueue>
#include <memory>

class QAsToLearnProvider : public IQAsToLearnProvider
{
public:
    QAsToLearnProvider(std::shared_ptr<IQAsToLearnCheckedByUserProvider> qAsCheckedByUserProvider);
    QQueue<std::shared_ptr<QA> > getQAs();

private:

    std::shared_ptr<IQAsToLearnCheckedByUserProvider> m_qAsCheckedByUserProvider;
};
