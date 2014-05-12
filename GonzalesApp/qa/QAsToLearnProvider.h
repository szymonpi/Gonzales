#ifndef QASTOLEARNPROVIDER_H
#define QASTOLEARNPROVIDER_H

#include "IQARepository.h"
#include <QQueue>
#include <memory>

class IQAsToLearnProvider
{
public:
    virtual QQueue<std::shared_ptr<QA> > getQAs() = 0;
    ~IQAsToLearnProvider(){}
};

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

#endif // QASTOLEARNPROVIDER_H
