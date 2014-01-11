#ifndef QAIMPORTER_H
#define QAIMPORTER_H

#include <error.h>

#include <QQueue>
#include <QFile>
#include <QStringList>
#include <QRegExp>
#include <QDebug>

#include "qacontainer.h"
#include "../file/filefactory.h"
#include "../file/file.h"

class QAFromTextFileImporter
{
public:
    QAFromTextFileImporter(std::shared_ptr<IFileFactory> fileFactory = std::make_shared<FileFactory>()):
        m_fileFactory(fileFactory)
    {}
    QQueue<QA> import(const QString &filePath);

private:
    std::shared_ptr<IFileFactory> m_fileFactory;
    QStringList getLinesFromFile(ReadableWritableFile &file);
    QStringList getSplittedCleanedLine(QString line);
    QString getQuestionFromSplittedLine(QStringList &splittedLine);
    void appendQAToQueue(QQueue<QA> &qAqueue, QStringList &splittedLine);
};

#endif // QAIMPORTER_H
