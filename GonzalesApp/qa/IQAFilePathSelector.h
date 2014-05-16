#pragma once

class QAFilePathSelector
{
public:
    virtual bool select() = 0;
    virtual QString getSelected() = 0;
    virtual ~QAFilePathSelector(){}
};
