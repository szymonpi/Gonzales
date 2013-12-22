#ifndef FILE_H
#define FILE_H

#include <QFile>
#include <QDataStream>

#include <string>
#include <cstring>
#include <memory>

class FileException : public std::runtime_error
{
public:
    FileException(std::string what):
        std::runtime_error(what)
    {}

};

class OpenableFile
{
public:
    virtual bool open(QFile::OpenModeFlag flags) = 0;
    virtual bool isWritable()=0;
    virtual bool isReadable()=0;
    virtual bool isOpen()=0;
};

class ReadableWritableFile : public virtual OpenableFile
{

public:
    virtual QString readLine() = 0;
    virtual QIODevice * getIODevice()=0;
};

class File : public ReadableWritableFile
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

    QString readLine()
    {
        char buffer[1024];

        if(file.readLine(buffer, sizeof(buffer))==-1)
            return QString();
        return QString::fromUtf8(buffer);
    }

    QIODevice* getIODevice()
    {
        return &file;
    }

    virtual bool isWritable()
    {
        return file.isWritable();
    }

    virtual bool isReadable()
    {
        return file.isReadable();
    }

    virtual bool isOpen()
    {
        return file.isOpen();
    }

    ~File()
    {
        file.close();
    }


private:
    QFile file;
};

#endif // FILE_H
