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
#include "../Common/SimpleTree/node.h"

class QAsImporter
{
public:
    virtual std::vector<std::shared_ptr<QA> > import(const QString &filePath) = 0;
    ~QAsImporter(){}
};

class QAFromTextFileImporter: public QAsImporter
{
public:
    QAFromTextFileImporter(std::shared_ptr<IFileFactory> fileFactory = std::make_shared<FileFactory>()):
        m_fileFactory(fileFactory)
    {}
    std::vector<std::shared_ptr<QA> > import(const QString &filePath);

private:
    std::shared_ptr<IFileFactory> m_fileFactory;
    QStringList getLinesFromFile(ReadableWritableFile &file);
    QStringList getSplittedCleanedLine(QString line);
    QString getQuestionFromSplittedLine(QStringList &splittedLine);
    void appendQa(std::vector<std::shared_ptr<QA> > &qAs, QStringList &splittedLine);
};

#endif // QAIMPORTER_H
