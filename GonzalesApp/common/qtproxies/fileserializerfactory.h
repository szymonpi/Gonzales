#ifndef FILESERIALIZERFACTORY_H
#define FILESERIALIZERFACTORY_H

#include "fileserializer.h"
#include "file.h"

class IFileSerializerFactory
{
public:
    virtual std::shared_ptr<CanSerializeData> create(QIODevice *device) const=0;
    ~IFileSerializerFactory(){}
};


class FileSerializerFactory : public IFileSerializerFactory
{
public:
    std::shared_ptr<CanSerializeData> create(QIODevice *device) const
    {
        return std::shared_ptr<CanSerializeData>(new FileSerializer(device));
    }
};

#endif // FILESERIALIZERFACTORY_H
