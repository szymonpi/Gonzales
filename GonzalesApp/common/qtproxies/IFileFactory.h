#pragma once

#include <memory>
#include "File.h"

class IFileFactory
{
public:
    virtual std::shared_ptr<IFile> create(const QString &filePath) const=0;
    virtual ~IFileFactory(){}
};
