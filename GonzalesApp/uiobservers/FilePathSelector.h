#pragma once
#include <QString>
class FilePathSelector
{
public:
    virtual bool select() = 0;
    virtual QString getSelected() const = 0;
    virtual ~FilePathSelector(){}
};
