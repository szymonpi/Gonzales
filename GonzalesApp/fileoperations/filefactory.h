#ifndef FILEFACTORY_H
#define FILEFACTORY_H

#include "file.h"

class IFileFactory
{
public:
    virtual std::shared_ptr<ReadableWritableFile> create(const QString &filePath) const=0;
    ~IFileFactory(){}
};


class FileFactory: public IFileFactory
{
public:
    std::shared_ptr<ReadableWritableFile> create(const QString &filePath) const
    {
        return std::make_shared<File>(filePath);
    }
};

#endif // FILEFACTORY_H
