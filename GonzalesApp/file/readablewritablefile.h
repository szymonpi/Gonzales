#ifndef READABLEWRITABLEFILE_H
#define READABLEWRITABLEFILE_H

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
    virtual void setFileName(const QString &fileName)=0;
};

class ReadableWritableFile : public virtual OpenableFile
{

public:
    virtual QString readLine() = 0;
    virtual QIODevice * getIODevice()=0;
};

#endif // READABLEWRITABLEFILE_H
