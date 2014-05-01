#ifndef FILEDESERIALIZER_H
#define FILEDESERIALIZER_H

#include <QDataStream>

class CanDeserializeData
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
    virtual QDataStream::Status status()=0;
    virtual bool atEnd()=0;

    ~CanDeserializeData(){}
};

class FileDeserializer: public CanDeserializeData
{
public:

    FileDeserializer(QIODevice *device):
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
        char *chars;
        stream >> chars;
        str = QString::fromLocal8Bit(chars, -1);
        delete chars;
    }


private:
    QDataStream stream;

};

#endif // FILEDESERIALIZER_H
