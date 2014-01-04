#include "qaimporter.h"



QStringList QAFromTextFileImporter::getLinesFromFile()
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

void QAFromTextFileImporter::appendQAToQueue(QQueue<QA> &qAqueue, QStringList &splittedLine)
{
    QString question = splittedLine.takeFirst();
    QString answer = splittedLine.takeFirst();
    qAqueue.append(QA(Question(question.toStdString()), Answer(answer.toStdString())));
}

QQueue<QA> QAFromTextFileImporter::import()
{
    if(!file.open(QFile::ReadOnly))
        throw FileException("Cant open file");
    QStringList lines = getLinesFromFile();

    QQueue<QA> qAqueue;
    foreach (QString line, lines) {
        QStringList splittedLine = getSplittedCleanedLine(line);
        if(splittedLine.size()==2)
            appendQAToQueue(qAqueue, splittedLine);
    }
    return qAqueue;
}
