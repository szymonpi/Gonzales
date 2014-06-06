#pragma once

#include <QDataStream>
#include "IDataDeserializer.h"

class DataDeserializer: public IDataDeserializer
{
public:

    DataDeserializer(QIODevice *device):
        stream(device)
    {
        stream.setVersion(QDataStream::Qt_5_1);
    }

    QDataStream::Status status()
    {
        return stream.status();
    }

    void deserialize(bool &i)
    {
        stream >> i;
    }

    void deserialize(qint8 &i)
    {
        stream >> i;
    }

    void deserialize(quint8 &i)
    {
        stream >> i;
    }

    void deserialize(quint16 &i)
    {
        stream >> i;
    }

    void deserialize(qint16 &i)
    {
        stream >> i;
    }

    void deserialize(qint32 &i)
    {
        stream >> i;
    }

    void deserialize(quint32 &i)
    {
        stream >> i;
    }

    void deserialize(qint64 &i)
    {
        stream >> i;
    }

    void deserialize(quint64 &i)
    {
        stream >> i;
    }

    void deserialize(float &i)
    {
        stream >> i;
    }

    void deserialize(double &i)
    {
        stream >> i;
    }

    void deserialize(char *&i)
    {
        stream >> i;
    }

    bool atEnd()
    {
        return stream.atEnd();
    }

    void deserialize(QString &str)
    {
        stream >> str;
    }


private:
    QDataStream stream;

};
