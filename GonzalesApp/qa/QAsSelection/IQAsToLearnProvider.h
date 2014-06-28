#pragma once

class QAView;

class IQAsToLearnProvider
{
public:
    virtual QQueue<std::shared_ptr<QAView> > getQAs() = 0;
    ~IQAsToLearnProvider(){}
};
