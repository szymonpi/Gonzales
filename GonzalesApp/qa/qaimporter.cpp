#include "qaimporter.h"

QStringList QAFromTextFileImporter::getLinesFromFile(ReadableWritableFile &file)
{
    QStringList lines;
    QString curretnLine = file.readLine();
    while(!curretnLine.isEmpty())
    {
        lines.append(curretnLine);
        curretnLine = file.readLine();
    };

    return lines;
}

QStringList QAFromTextFileImporter::getSplittedCleanedLine(QString line)
{
    QRegExp whitespaces("\\s+");
    QStringList splittedLine = line.split(whitespaces);
    splittedLine.removeAll(QString(""));
    return splittedLine;
}

void QAFromTextFileImporter::appendQa(Node<QA> &qAqueue, QStringList &splittedLine)
{
    QString question = splittedLine.takeFirst();
    QString answer = splittedLine.takeFirst();
    qAqueue.append(std::make_shared<QA>(Question(question.toStdString()), Answer(answer.toStdString())));
}

Node<QA> QAFromTextFileImporter::import(const QString &filePath)
{
    std::shared_ptr<ReadableWritableFile> file = m_fileFactory->create(filePath);
    if(!file->open(QFile::ReadOnly))
        throw FileException("Can't open file");
    QStringList lines = getLinesFromFile(*file);

    Node<QA> qAqueue;
    foreach (QString line, lines) {
        QStringList splittedLine = getSplittedCleanedLine(line);
        if(splittedLine.size()==2)
            appendQa(qAqueue, splittedLine);
    }
    return qAqueue;
}
