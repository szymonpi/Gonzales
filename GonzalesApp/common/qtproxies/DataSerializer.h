#pragma once

#include <QDataStream>
#include <QString>
#include "IDataSerializer.h"

class DataSerializer : public IDataSerializer
{
public:

    DataSerializer(QIODevice *device):
        stream(device)
    {
        stream.setVersion(QDataStream::Qt_5_1);
    }

    QDataStream::Status status()
    {
        return stream.status();
    }


    void serialize(bool i)
    {
        stream << i;
    }

    void serialize(qint8 i)
    {
        stream << i;
    }

    void serialize(quint8 i)
    {
        stream << i;
    }

    void serialize(quint16 i)
    {
        stream << i;
    }

    void serialize(qint16 i)
    {
        stream << i;
    }

    void serialize(qint32 i)
    {
        stream << i;
    }

    void serialize(quint32 i)
    {
        stream << i;
    }

    void serialize(qint64 i)
    {
        stream << i;
    }

    void serialize(quint64 i)
    {
        stream << i;
    }

    void serialize(float i)
    {
        stream << i;
    }

    void serialize(double i)
    {
        stream << i;
    }

    void serialize(const char *i)
    {
        stream << i;
    }

    virtual void serialize(const QString &str)
    {
        stream << str.toStdString().c_str();
    }

private:
    QDataStream stream;

};
