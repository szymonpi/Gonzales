#pragma once
#include "IFileFactory.h"

class FileFactory: public IFileFactory
{
public:
    std::shared_ptr<IFile> create(const QString &filePath) const
    {
        return std::make_shared<File>(filePath);
    }
};
