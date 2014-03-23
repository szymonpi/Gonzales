#include <QQueue>

#include "qasaver.h"
#include "../Common/simpletree.h"


QASaver::QASaver(std::shared_ptr<IFileFactory> fileFactory,
                 std::shared_ptr<IFileSerializerFactory> fileSerializerFactory):
    fileFactory(fileFactory),
    fileSerializerFactory(fileSerializerFactory)
{
}

void QASaver::openFile(ReadableWritableFile &file)
{
    if(!file.open(QFile::WriteOnly))
        throw FileException("File isn't open");
}

void QASaver::serializeFileVersion(CanSerializeData &serializer)
{
    serializer.serialize(static_cast<quint16>(QAFileVersion1));
}

void QASaver::serializeQA(CanSerializeData &serializer, const QA &qa) const
{
    qa.question.serialize(serializer);
    qa.answer.serialize(serializer);
}

void QASaver::save(const Node<QA> &questionAnswers, const QString &userName)
{
    QString fileName = getFilePathToQas(userName);
    std::shared_ptr<ReadableWritableFile> file = fileFactory->create(fileName);
    openFile(*file);
    std::shared_ptr<CanSerializeData> serializer = fileSerializerFactory->create(file->getIODevice());
    serializeFileVersion(*serializer);

    foreach(Node<QA> qA, questionAnswers.getNodes())
    {
        std::shared_ptr<QA> qap = qA.getNodeValue();
        if(qap)
            serializeQA(*serializer, *qap);
    }

    if(serializer->status()!=QDataStream::Ok)
        throw FileException("Something wen't wrong when saving file");
}
