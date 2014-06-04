#include "QAsToLearnProvider.h"
#include "../../Common/SimpleTree/Node.h"
#include <memory>
#include "../../Common/Common.h"
#include <QVector>

QAsToLearnProvider::QAsToLearnProvider(std::shared_ptr<IQAsToLearnCheckedByUserProvider> qasToLearnProvider,
                                       std::shared_ptr<IQAsSelector> qasSelector):
    m_qAsCheckedByUserProvider(qasToLearnProvider),
    m_selector(qasSelector)
{
}

QQueue<std::shared_ptr<QA> > QAsToLearnProvider::getQAs()
{
    std::vector<std::shared_ptr<QA>> userCheckedQAs = m_qAsCheckedByUserProvider->getQAs();
    std::vector<std::shared_ptr<QA>> selectedToLearnQAs = m_selector->select(userCheckedQAs);

    QQueue<std::shared_ptr<QA>> qas;
    for(const std::shared_ptr<QA> &elem: selectedToLearnQAs)
    {
        qas.push_back(elem);
    }
    return qas;
}

