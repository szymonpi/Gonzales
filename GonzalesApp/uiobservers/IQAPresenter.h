#pragma once

class IQAPresenter
{
public:
    virtual void presentQuestion(const QString &question) = 0;
    virtual void presentAnswer(const QString &question) = 0;
    virtual ~IQAPresenter(){}
};
