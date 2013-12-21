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
    virtual QString readLine() = 0;

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

    QString readLine()
    {
        char buffer[1024];

        if(file.readLine(buffer, sizeof(buffer))==-1)
            return QString();
        return QString::fromUtf8(buffer);
    }

private:
    QFile file;
};

#endif // FILE_H
