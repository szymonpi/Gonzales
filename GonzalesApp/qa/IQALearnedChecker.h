#pragma once

class QA;

class IQALearnedChecker
{
public:
    ~IQALearnedChecker(){}
    virtual bool isLearned(const QA &qa) = 0;
};
