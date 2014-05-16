#pragma once

#include "File.h"

class IFileFactory
{
public:
    virtual std::shared_ptr<IFile> create(const QString &filePath) const=0;
    ~IFileFactory(){}
};


class FileFactory: public IFileFactory
{
public:
    std::shared_ptr<IFile> create(const QString &filePath) const
    {
        return std::make_shared<File>(filePath);
    }
};
