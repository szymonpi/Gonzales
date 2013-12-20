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

class QAFromTextFileImporter: public CanImportQA
{
public:
    QAFromTextFileImporter(ReadableFile &file):
        file(file)
    {}
    QQueue<QA> import();

private:
    ReadableFile &file;
    QStringList getLinesFromFile();
    void openFile();
    QStringList getSplittedCleanedLine(QString line);
    QString getQuestionFromSplittedLine(QStringList &splittedLine);
    void appendQAToQueue(QQueue<QA> &qAqueue, QStringList &splittedLine);
};

#endif // QAIMPORTER_H
