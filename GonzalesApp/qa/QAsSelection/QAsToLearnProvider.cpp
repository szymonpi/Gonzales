#include "QAsToLearnProvider.h"
#include "../../common/SimpleTree/Node.h"
#include <memory>
#include "../../common/Common.h"
#include <QVector>

QAsToLearnProvider::QAsToLearnProvider(std::shared_ptr<IQAsToLearnCheckedByUserProvider> qasToLearnProvider,
                                       std::shared_ptr<IQAsSelector> qasSelector,
                                       std::shared_ptr<QAToViewConverter> m_converter):
    m_qAsCheckedByUserProvider(qasToLearnProvider),
    m_selector(qasSelector),
    m_converter(m_converter)
{
}

QQueue<std::shared_ptr<QAView> > QAsToLearnProvider::getQAs()
{
    std::vector<std::shared_ptr<QA>> userCheckedQAs = m_qAsCheckedByUserProvider->getQAs();
    std::vector<std::shared_ptr<QA>> selectedToLearnQAs = m_selector->select(userCheckedQAs);

    QQueue<std::shared_ptr<QAView>> qas;
    for(const auto& elem: selectedToLearnQAs)
    {
        qas.push_back(m_converter->convert(elem));
    }
    return qas;
}

