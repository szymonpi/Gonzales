#ifndef FILE_H
#define FILE_H

#include <QFile>

#include <string>
#include <cstring>

class OpenableFile
{
public:
    virtual bool open(QFile::OpenModeFlag flags) = 0;
    virtual void setFileName(const QString &fileName) = 0;
};

class ReadableFile : public virtual OpenableFile
{

public:
    virtual QByteArray readAll()=0;
    virtual qint64 readLine(char *data, qint64 maxlen) = 0;
    virtual QByteArray readLine(qint64 maxlen = 0) = 0;

};

class File : public ReadableFile
{

public:
    File(QString filePath):
        file(filePath)
    {
    }

    File():
        file("")
    {
    }

    bool open(QFile::OpenModeFlag flags)
    {
        return file.open(flags);
    }

    void setFileName(const QString &fileName)
    {
        file.setFileName(fileName);
    }

    qint64 readLine(char *data, qint64 maxlen)
    {
        return file.readLine(data, maxlen);
    }

    QByteArray readLine(qint64 maxlen = 0)
    {
        return file.readLine(maxlen);
    }

    QByteArray readAll()
    {
        return file.readAll();
    }

private:
    QFile file;
};

#endif // FILE_H
