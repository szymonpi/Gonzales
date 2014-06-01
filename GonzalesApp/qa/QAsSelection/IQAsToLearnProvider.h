#pragma once

class IQAsToLearnProvider
{
public:
    virtual QQueue<std::shared_ptr<QA> > getQAs() = 0;
    ~IQAsToLearnProvider(){}
};
