#pragma once

class QString;
class QIODevice;

class IFile
{
public:
    virtual bool open(QFile::OpenModeFlag flags) = 0;
    virtual void close() = 0;
    virtual bool isWritable() = 0;
    virtual bool isReadable() = 0;
    virtual bool isOpen() = 0;
    virtual void setFileName(const QString &fileName) = 0;
    virtual QString readLine() = 0;
    virtual QIODevice * getIODevice()=0;

    virtual ~IFile(){}
};

