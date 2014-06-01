#ifndef QASTOLEARNCHECKEDBYUSERPROVIDER_H
#define QASTOLEARNCHECKEDBYUSERPROVIDER_H

#include "../IQARepository.h"
#include "IQAsToLearnProvider.h"
#include <QVector>
#include <memory>
#include "IQAsToLearnCheckedByUserProvider.h"

class QAsToLearnCheckedByUserProvider: public IQAsToLearnCheckedByUserProvider
{
public:

    QAsToLearnCheckedByUserProvider(std::shared_ptr<QAsProvider> qasProvider);
    QVector<std::shared_ptr<QA> > getQAs() override;

private:
    void fillQAsToLearn(QVector<std::shared_ptr<QA> > &qasToLearn,
                                            const SimpleTree::Node<QA> &node) const;
    bool canBeThereSomethingToLearn(const SimpleTree::Node<QA> &rootNode) const;
    std::shared_ptr<QAsProvider> m_qasProvider;
};

#endif // QASTOLEARNCHECKEDBYUSERPROVIDER_H
