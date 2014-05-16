#pragma once

#include "filedeserializer.h"
#include "file.h"

class IFileDeserializerFactory
{
public:
    virtual std::shared_ptr<CanDeserializeData> create(QIODevice *device) const=0;
    ~IFileDeserializerFactory(){}
};


class FileDeserializerFactory : public IFileDeserializerFactory
{
public:
    std::shared_ptr<CanDeserializeData> create(QIODevice *device) const
    {
        return std::shared_ptr<CanDeserializeData>(new FileDeserializer(device));
    }
};
