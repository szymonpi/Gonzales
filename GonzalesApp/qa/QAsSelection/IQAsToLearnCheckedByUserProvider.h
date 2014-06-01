#pragma once
#include <QVector>

class IQAsToLearnCheckedByUserProvider
{
public:
    virtual QVector<std::shared_ptr<QA> > getQAs() = 0;
    virtual ~IQAsToLearnCheckedByUserProvider(){}
};
