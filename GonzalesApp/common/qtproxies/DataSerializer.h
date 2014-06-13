#pragma once

#include <QDataStream>
#include <QString>
#include <QDateTime>
#include "IDataSerializer.h"

class DataSerializer : public IDataSerializer
{
public:

    DataSerializer(QIODevice *device):
        stream(device)
    {
        stream.setVersion(QDataStream::Qt_5_1);
    }

    QDataStream::Status status() override
    {
        return stream.status();
    }


    void serialize(bool i) override
    {
        stream << i;
    }

    void serialize(qint8 i) override
    {
        stream << i;
    }

    void serialize(quint8 i) override
    {
        stream << i;
    }

    void serialize(quint16 i) override
    {
        stream << i;
    }

    void serialize(qint16 i) override
    {
        stream << i;
    }

    void serialize(qint32 i) override
    {
        stream << i;
    }

    void serialize(quint32 i) override
    {
        stream << i;
    }

    void serialize(qint64 i) override
    {
        stream << i;
    }

    void serialize(quint64 i) override
    {
        stream << i;
    }

    void serialize(float i) override
    {
        stream << i;
    }

    void serialize(double i) override
    {
        stream << i;
    }

    void serialize(const char *i) override
    {
        stream << i;
    }

    void serialize(const QString &str) override
    {
        stream << str;
    }

    void serialize(const QDateTime& dateTime) override
    {
        stream << dateTime;
    }

    void serialize(const QDate& dateTime) override
    {
        stream << dateTime;
    }

private:
    QDataStream stream;

};
