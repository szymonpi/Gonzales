#pragma once

#include "IQARepository.h"
#include "IQAsToLearnProvider.h"
#include <QQueue>
#include <memory>

class QAsToLearnProvider : public IQAsToLearnProvider
{
public:
    QAsToLearnProvider(std::shared_ptr<QAsProvider> qasProvider);
    QQueue<std::shared_ptr<QA> > getQAs();

private:
    void fillQAsToLearn(QQueue<std::shared_ptr<QA> > &qasToLearn,
                                            const SimpleTree::Node<QA> &node) const;
    bool canBeThereSomethingToLearn(const SimpleTree::Node<QA> &rootNode) const;
    std::shared_ptr<QAsProvider> m_qasProvider;
};
