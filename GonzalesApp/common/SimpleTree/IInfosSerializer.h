#pragma once
#include "../qtproxies/DataDeserializer.h"
#include "../qtproxies/DataSerializer.h"
#include <map>


namespace SimpleTree
{

namespace Utils
{

class IInfosSerializer
{
public:
    virtual void deserialize(IDataDeserializer &deserializer, std::map<quint8, QVariant>& infos) = 0;
    virtual void serialize(IDataSerializer &serializer, const std::map<quint8, QVariant>& infos) = 0;
    virtual ~IInfosSerializer(){}
};


}

}
