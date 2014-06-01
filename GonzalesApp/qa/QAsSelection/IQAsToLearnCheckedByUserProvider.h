#pragma once
#include <QVector>

class IQAsToLearnCheckedByUserProvider
{
public:
    virtual std::vector<std::shared_ptr<QA> > getQAs() = 0;
    virtual ~IQAsToLearnCheckedByUserProvider(){}
};
