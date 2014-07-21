#pragma once

class QA;

class IQALearnedChecker
{
public:
    virtual ~IQALearnedChecker(){}
    virtual bool isLearned(const QA &qa) = 0;
};
