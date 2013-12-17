#ifndef QAIMPORTER_H
#define QAIMPORTER_H

#include <error.h>

#include <QQueue>
#include <QFile>
#include <QStringList>
#include <QRegExp>
#include <QDebug>

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

        QStringList lines;
        QString curretnLine = file.readLine();

        while(!curretnLine.isEmpty())
        {
            lines.append(curretnLine);
            curretnLine = file.readLine();
        };

        QQueue<QA> qAqueue;
        foreach (QString line, lines) {

            QRegExp whitespaces("\\s+");
            QStringList qas = line.split(whitespaces);
            if(qas.isEmpty())
                continue;
            QString question = qas.takeFirst().trimmed();

            if(question.isEmpty())
                continue;

            if(qas.isEmpty())
                continue;
            QString answer = qas.takeFirst().trimmed();
            if(answer.isEmpty())
                continue;
            qDebug() << answer;

            qAqueue.append(QA(Question(question.toStdString()),
                              Answer(answer.toStdString())));
        }

        return qAqueue;
    }

private:
    ReadableFile &file;
};

#endif // QAIMPORTER_H
