#ifndef QAIMPORTER_H
#define QAIMPORTER_H

#include <error.h>

#include <QQueue>
#include <QFile>
#include <QStringList>
#include <QRegExp>
#include <QDebug>

#include "qacontainer.h"
#include "../common/qtproxies/filefactory.h"
#include "../common/qtproxies/file.h"

class QAFromTextFileImporter
{
public:
    QAFromTextFileImporter(std::shared_ptr<IFileFactory> fileFactory = std::make_shared<FileFactory>()):
        m_fileFactory(fileFactory)
    {}
    std::list<QA> import(const QString &filePath);

private:
    std::shared_ptr<IFileFactory> m_fileFactory;
    QStringList getLinesFromFile(ReadableWritableFile &file);
    QStringList getSplittedCleanedLine(QString line);
    QString getQuestionFromSplittedLine(QStringList &splittedLine);
    void pushQa(std::list<QA> &qAqueue, QStringList &splittedLine);
};

#endif // QAIMPORTER_H
