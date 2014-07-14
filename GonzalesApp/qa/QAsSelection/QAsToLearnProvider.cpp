#include "QAsToLearnProvider.h"
#include "../../common/SimpleTree/Node.h"
#include <memory>
#include "../../common/Common.h"
#include <QVector>

QAsToLearnProvider::QAsToLearnProvider(std::shared_ptr<IQAsToLearnCheckedByUserProvider> qasToLearnProvider,
                                       std::shared_ptr<IQAsSelector> qasSelector):
    m_qAsCheckedByUserProvider(qasToLearnProvider),
    m_selector(qasSelector)
{
}

QQueue<std::shared_ptr<QAView> > QAsToLearnProvider::getQAs()
{
    std::vector<std::shared_ptr<QA>> userCheckedQAs = m_qAsCheckedByUserProvider->getQAs();
    std::vector<std::shared_ptr<QAView>> selectedToLearnQAs = m_selector->select(userCheckedQAs);

    QQueue<std::shared_ptr<QAView>> qas;
    for(const std::shared_ptr<QAView> &elem: selectedToLearnQAs)
    {
        qas.push_back(elem);
    }
    return qas;
}

