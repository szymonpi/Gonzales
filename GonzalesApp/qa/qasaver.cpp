#include <QQueue>

#include "qasaver.h"


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

void QASaver::serializeQA(CanSerializeData &serializer, const QA &qa)
{
    std::string question= qa.question.getAsString();
    std::string answer= qa.answer.getAsString();

    serializer.serialize(question.c_str());
    serializer.serialize(answer.c_str());
}

void QASaver::save(const std::list<QA> &questionAnswers, const QString &filePath)
{
    std::shared_ptr<ReadableWritableFile> file = fileFactory->create(filePath);
    openFile(*file);
    std::shared_ptr<CanSerializeData> serializer = fileSerializerFactory->create(file->getIODevice());
    serializeFileVersion(*serializer);

    foreach(QA qA, questionAnswers)
        serializeQA(*serializer, qA);

    if(serializer->status()!=QDataStream::Ok)
        throw FileException("Something wen't wrong when saving file");
}
