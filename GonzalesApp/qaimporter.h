#ifndef QAIMPORTER_H
#define QAIMPORTER_H

#include <error.h>

#include <QQueue>
#include <QFile>
#include <QStringList>

#include "qacontainer.h"
#include "file.h"


class FileException : public std::runtime_error
{
public:
    FileException(std::string what):
        std::runtime_error(what)
    {}

};

class CanImportQA
{
public:
    virtual QQueue<QA> import()=0;
};

class QAImporter//: public CanImportQA
{
public:
    QAImporter(ReadableFile &file):
        file(file)
    {}

    QQueue<QA> import()
    {
        if(!file.open(QFile::ReadOnly))
            throw(FileException("Can't open file!"));

        char buffer[10240];


        qint64 lineSize = file.readLine(buffer, sizeof(buffer));
        QStringList lines;

        while(lineSize != -1)
        {
            lines.append(QString::fromLocal8Bit(buffer, sizeof(buffer)));
            lineSize = file.readLine(buffer, sizeof(buffer));
        };

        QQueue<QA> qAqueue;
        foreach (QString line, lines) {

            QStringList qa = line.split(" ");
            QString question = qa.takeFirst();
            QString answer = qa.takeFirst();

            qAqueue.append(QA(Question(question.toStdString()),
                              Answer(answer.toStdString())));
        }

        return qAqueue;
    }

private:
    ReadableFile &file;
};

#endif // QAIMPORTER_H
