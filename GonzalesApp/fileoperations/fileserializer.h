#ifndef FILESERIALIZER_H
#define FILESERIALIZER_H

#include <QDataStream>

class CanSerializeData{
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
    virtual QDataStream::Status status()=0;
    ~CanSerializeData(){}
};

class CanDeserializeData
{
public:

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
    virtual QDataStream::Status status()=0;

    ~CanDeserializeData(){}
};

class FileSerializer : public CanSerializeData
{
public:

    FileSerializer(QIODevice *device):
        stream(device)
    {
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

private:
    QDataStream stream;

};

class FileDeserializer: public CanDeserializeData
{
public:

    FileDeserializer(QIODevice *device):
        stream(device)
    {
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

private:
    QDataStream stream;

};

#endif // FILESERIALIZER_H
