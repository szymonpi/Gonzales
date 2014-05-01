#ifndef FILEPATHSELECTOR_H
#define FILEPATHSELECTOR_H
#include <QString>
class FilePathSelector
{
public:
    virtual bool select() = 0;
    virtual QString getSelected() const = 0;
    virtual ~FilePathSelector(){}
};

#endif // FILEPATHSELECTOR_H
