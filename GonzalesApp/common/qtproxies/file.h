#ifndef FILE_H
#define FILE_H

#include <QFile>
#include <QDataStream>

#include <string>
#include <cstring>
#include <memory>

#include "IFile.h"

class File : public IFile
{

public:
    File(const QString &filePath):
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
