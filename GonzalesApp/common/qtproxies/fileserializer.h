#ifndef FILESERIALIZER_H
#define FILESERIALIZER_H

#include <QDataStream>
#include <QString>

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
    virtual void serialize(const QString &str)=0;
    virtual QDataStream::Status status()=0;
    ~CanSerializeData(){}
};

class FileSerializer : public CanSerializeData
{
public:

    FileSerializer(QIODevice *device):
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

#endif // FILESERIALIZER_H
