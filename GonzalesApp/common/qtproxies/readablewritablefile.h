#ifndef READABLEWRITABLEFILE_H
#define READABLEWRITABLEFILE_H
#include "../FileException.h"

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
