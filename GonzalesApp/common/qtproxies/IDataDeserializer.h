#pragma once
#include <QDataStream>

class IDataDeserializer
{
public:

    virtual void deserialize(bool &i)=0;
    virtual void deserialize(qint8 &i)=0;
    virtual void deserialize(quint8 &i)=0;
    virtual void deserialize(quint16 &i)=0;
    virtual void deserialize(qint16 &i)=0;
    virtual void deserialize(qint32 &i)=0;
    virtual void deserialize(quint32 &i)=0;
    virtual void deserialize(qint64 &i)=0;
    virtual void deserialize(quint64 &i)=0;
    virtual void deserialize(float &i)=0;
    virtual void deserialize(double &i)=0;
    virtual void deserialize(char *&i)=0;
    virtual void deserialize(QString &str)=0;
    virtual void deserialize(QDateTime &dateTime)=0;
    virtual void deserialize(QDate &date)=0;
    virtual void deserialize(std::string& str)=0;
    virtual QDataStream::Status status()=0;
    virtual bool atEnd()=0;

    virtual ~IDataDeserializer(){}
};
