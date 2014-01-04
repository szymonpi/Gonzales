#ifndef QAIMPORTER_H
#define QAIMPORTER_H

#include <error.h>

#include <QQueue>
#include <QFile>
#include <QStringList>
#include <QRegExp>
#include <QDebug>

#include "qacontainer.h"
#include "../file/file.h"
class CanImportQA
{
public:
    virtual QQueue<QA> import()=0;
};

class QAFromTextFileImporter: public CanImportQA
{
public:
    QAFromTextFileImporter(ReadableWritableFile &file):
        file(file)
    {}
    QQueue<QA> import();

private:
    ReadableWritableFile &file;
    QStringList getLinesFromFile();
    QStringList getSplittedCleanedLine(QString line);
    QString getQuestionFromSplittedLine(QStringList &splittedLine);
    void appendQAToQueue(QQueue<QA> &qAqueue, QStringList &splittedLine);
};

#endif // QAIMPORTER_H
