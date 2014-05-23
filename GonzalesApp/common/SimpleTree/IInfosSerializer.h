#pragma once
#include "../qtproxies/DataDeserializer.h"
#include "../qtproxies/DataSerializer.h"


namespace SimpleTree
{

namespace Utils
{

class IInfosSerializer
{
public:
    virtual void deserialize(IDataDeserializer &deserializer, QMap<quint8, QVariant>& infos) = 0;
    virtual void serialize(IDataSerializer &serializer, const QMap<quint8, QVariant>& infos) = 0;
    ~IInfosSerializer(){}
};


}

}
