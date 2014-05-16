#pragma once
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

class IFile : public virtual OpenableFile
{

public:
    virtual QString readLine() = 0;
    virtual QIODevice * getIODevice()=0;
};

