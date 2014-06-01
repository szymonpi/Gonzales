#include "QAsToLearnProvider.h"
#include "../../Common/SimpleTree/Node.h"
#include <memory>
#include "../../Common/Common.h"
#include <QVector>

QAsToLearnProvider::QAsToLearnProvider(std::shared_ptr<IQAsToLearnCheckedByUserProvider> qasToLearnProvider):
    m_qAsCheckedByUserProvider(qasToLearnProvider)
{
}

QQueue<std::shared_ptr<QA> > QAsToLearnProvider::getQAs()
{
    QVector<std::shared_ptr<QA>> userCheckedQAs = m_qAsCheckedByUserProvider->getQAs();

    QQueue<std::shared_ptr<QA>> qas;
    for(const std::shared_ptr<QA> &elem: userCheckedQAs)
    {
        qas.push_back(elem);
    }
    return qas;
}

