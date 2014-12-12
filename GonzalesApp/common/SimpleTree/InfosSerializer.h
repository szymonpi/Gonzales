#pragma once

#include "IInfosSerializer.h"
#include "Utils.h"
#include <QVariant>
#include <memory>
#include <cassert>
#include <iostream>
#include <utility>

namespace SimpleTree
{

namespace Utils
{

class IInfoSerializer
{
public:
    virtual QVariant deserialize(IDataDeserializer& deserializer) = 0;
    virtual void serialize(IDataSerializer& serializer, const QVariant &v, const quint8 nodeInfoRole) = 0;
    ~IInfoSerializer(){}
};

template <class T>
class InfoSerializer: public IInfoSerializer
{
public:
    QVariant deserialize(IDataDeserializer& deserializer) override
    {
        T value;
        deserializer.deserialize(value);
        return value;
    }

    virtual void serialize(IDataSerializer& serializer, const QVariant &v, const quint8 nodeInfoRole) override
    {
        serializer.serialize(nodeInfoRole);
        serializer.serialize(v.type());
        serializer.serialize(v.value<T>());
    }
};

class InfosSerializer: public IInfosSerializer
{
public:
    InfosSerializer()
    {
        infoSerializers.emplace(std::make_pair(QVariant::Bool, std::unique_ptr<IInfoSerializer>{new InfoSerializer<bool>()}));
        infoSerializers.emplace(std::make_pair(QVariant::UInt, std::unique_ptr<IInfoSerializer>{new InfoSerializer<unsigned>()}));
        infoSerializers.emplace(std::make_pair(QVariant::Int, std::unique_ptr<IInfoSerializer>{new InfoSerializer<int>()}));
        infoSerializers.emplace(std::make_pair(QVariant::LongLong, std::unique_ptr<IInfoSerializer>{new InfoSerializer<long long>()}));
        infoSerializers.emplace(std::make_pair(QVariant::ULongLong, std::unique_ptr<IInfoSerializer>{new InfoSerializer<unsigned long long>()}));
        infoSerializers.emplace(std::make_pair(QVariant::Double, std::unique_ptr<IInfoSerializer>{new InfoSerializer<double>()}));
        infoSerializers.emplace(std::make_pair(QVariant::String, std::unique_ptr<IInfoSerializer>{new InfoSerializer<QString>()}));
        infoSerializers.emplace(std::make_pair(QVariant::Bool, std::unique_ptr<IInfoSerializer>{new InfoSerializer<bool>()}));
    }
public:
    void deserialize(IDataDeserializer& deserializer,
                     std::map<quint8, QVariant>& infos) override
    {
        int infosSize = 0;
        deserializer.deserialize(infosSize);
        for(int i = 0; i < infosSize; ++i)
        {
            quint8 nodeInfoRole = 0;
            unsigned type = 0;
            deserializer.deserialize(nodeInfoRole);
            deserializer.deserialize(type);

            try
            {
                infos[nodeInfoRole] = infoSerializers.at(QVariant::Type(type))->deserialize(deserializer);
            }
            catch(const std::out_of_range &e)
            {
                std::cerr << "NO TYPE IN MAP infoDeserializers!";
                abort();
            }
        }
    }

    virtual void serialize(IDataSerializer &serializer,
                           const std::map<quint8, QVariant>& infos) override
    {
        serializer.serialize(infos.size());
        for(auto it = infos.begin(); it != infos.end(); ++it)
        {
            try
            {
                infoSerializers.at(it->second.type())->serialize(serializer, it->second, it->first);
            }
            catch(const std::out_of_range &e)
            {
                std::cerr << "NO TYPE IN MAP infoSerializers!";
                abort();
            }
        }
    }
private:
    std::map<QVariant::Type, std::unique_ptr<IInfoSerializer>> infoSerializers;
};


}

}
