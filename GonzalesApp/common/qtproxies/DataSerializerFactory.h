#pragma once

#include "DataSerializer.h"
#include "File.h"

class IDataSerializerFactory
{
public:
    virtual std::shared_ptr<IDataSerializer> create(QIODevice *device) const=0;
    virtual ~IDataSerializerFactory(){}
};


class DataSerializerFactory : public IDataSerializerFactory
{
public:
    std::shared_ptr<IDataSerializer> create(QIODevice *device) const
    {
        return std::shared_ptr<DataSerializer>(new DataSerializer(device));
    }
};
