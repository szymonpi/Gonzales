#pragma once

class IDataSerializer{
public:
    virtual void serialize(bool i)=0;
    virtual void serialize(qint8 i)=0;
    virtual void serialize(quint8 i)=0;
    virtual void serialize(quint16 i)=0;
    virtual void serialize(qint16 i)=0;
    virtual void serialize(qint32 i)=0;
    virtual void serialize(quint32 i)=0;
    virtual void serialize(qint64 i)=0;
    virtual void serialize(quint64 i)=0;
    virtual void serialize(float i)=0;
    virtual void serialize(double i)=0;
    virtual void serialize(const char *i)=0;
    virtual void serialize(const QString &str)=0;
    virtual void serialize(const QDateTime& dateTime)=0;
    virtual void serialize(const QDate& dateTime)=0;

    virtual QDataStream::Status status()=0;
    ~IDataSerializer(){}
};
