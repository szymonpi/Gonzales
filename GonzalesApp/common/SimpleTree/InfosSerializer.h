#pragma once

#include "IInfosSerializer.h"
#include "Utils.h"
#include <QVariant>

namespace SimpleTree
{

namespace Utils
{

class InfosSerializer: public IInfosSerializer
{
public:
    void deserialize(IDataDeserializer&deserializer,
                     QMap<quint8, QVariant>& infos) override
    {
        int infosSize = 0;
        deserializer.deserialize(infosSize);
        for(int i = 0; i < infosSize; ++i)
        {
            quint8 nodeInfoRole = 0;
            unsigned type = 0;
            QVariant valueVariant;
            deserializer.deserialize(nodeInfoRole);
            deserializer.deserialize(type);

            switch(QVariant::Type(type))
            {
                case QVariant::Bool:
                {
                    bool value;
                    deserializer.deserialize(value);
                    valueVariant.setValue(value);
                    break;
                }
                case QVariant::UInt:
                {
                    unsigned value;
                    deserializer.deserialize(value);
                    valueVariant.setValue(value);
                    break;
                }
                case QVariant::Int:
                {
                    int value;
                    deserializer.deserialize(value);
                    valueVariant.setValue(value);
                    break;
                }
                case QVariant::LongLong:
                {
                    long long value;
                    deserializer.deserialize(value);
                    valueVariant.setValue(value);
                    break;
                }
                case QVariant::ULongLong:
                {
                    unsigned long long value;
                    deserializer.deserialize(value);
                    valueVariant.setValue(value);
                    break;
                }
                case QVariant::Double:
                {
                    double value;
                    deserializer.deserialize(value);
                    valueVariant.setValue(value);
                    break;
                }
                case QVariant::String:
                {
                    QString value;
                    deserializer.deserialize(value);
                    valueVariant.setValue(value);
                    break;
                }
                default:
                    throw std::logic_error("not supported type in info map");
                    break;
            }
            infos[nodeInfoRole] = valueVariant;
        }
    }

    virtual void serialize(IDataSerializer &serializer,
                           const QMap<quint8, QVariant>& infos) override
    {
        serializer.serialize(infos.size());
        for(auto it = infos.begin(); it != infos.end(); ++it)
        {
            const QVariant &v = it.value();
            unsigned type = unsigned(v.type());
            switch(v.type())
            {
                case QVariant::Bool:
                    serializer.serialize(it.key());
                    serializer.serialize(type);
                    serializer.serialize(v.value<bool>());
                    break;
                case QVariant::UInt:
                    serializer.serialize(it.key());
                    serializer.serialize(type);
                    serializer.serialize(v.value<unsigned>());
                    break;
                case QVariant::Int:
                    serializer.serialize(it.key());
                    serializer.serialize(type);
                    serializer.serialize(v.value<int>());
                    break;
                case QVariant::LongLong:
                    serializer.serialize(it.key());
                    serializer.serialize(type);
                    serializer.serialize(v.value<long long int>());
                    break;
                case QVariant::ULongLong:
                    serializer.serialize(it.key());
                    serializer.serialize(type);
                    serializer.serialize(v.value<unsigned long long int>());
                    break;
                case QVariant::Double:
                    serializer.serialize(it.key());
                    serializer.serialize(type);
                    serializer.serialize(v.value<double>());
                    break;
                case QVariant::String:
                    serializer.serialize(it.key());
                    serializer.serialize(type);
                    serializer.serialize(v.value<QString>());
                    break;
                default:
                    throw std::logic_error("not supported type in info map");
                    break;
            }
        }
    }
};


}

}
