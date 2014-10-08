#ifndef DUPA
#define DUPA

#include <error.h>

#include <QStringList>

#include "../QA.h"
#include "../../common/qtproxies/FileFactory.h"
#include "../../common/qtproxies/IFile.h"
#include "../../common/SimpleTree/Node.h"
#include "LineToImportSplitter.h"

class QAsImporter
{
public:
    virtual std::vector<std::shared_ptr<QA> > import(const QString &filePath) = 0;
    virtual ~QAsImporter(){}
};

class QAFromTextFileImporter: public QAsImporter
{
public:
    QAFromTextFileImporter(std::shared_ptr<ILineToImportSplitter> lineSplitter = std::make_shared<LineToImportSplitter>(),
                           std::shared_ptr<IFileFactory> fileFactory = std::make_shared<FileFactory>()):
        m_lineSplitter(lineSplitter),
        m_fileFactory(fileFactory)
    {}
    std::vector<std::shared_ptr<QA> > import(const QString &filePath);

private:
    void appendQa(std::vector<std::shared_ptr<QA> > &qAs, QStringList &splittedLine);
    QStringList getLinesFromFile(IFile &file);
    QStringList getSplittedCleanedLine(QString line);
    QString getQuestionFromSplittedLine(QStringList &splittedLine);
    std::shared_ptr<ILineToImportSplitter> m_lineSplitter;
    std::shared_ptr<IFileFactory> m_fileFactory;
};


#endif
