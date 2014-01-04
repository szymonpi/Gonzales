#include <QQueue>

#include "qasaver.h"


QASaver::QASaver(ReadableWritableFile &file, std::shared_ptr<IFileSerializerFactory> fileSerializerFactory):
    file(file),
    fileSerializerFactory(fileSerializerFactory)
{
}

void QASaver::validateFile()
{
    if(!file.isOpen())
        throw FileException("File isn't open");
    if(!file.isWritable())
        throw FileException("File isn't writable");
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

bool QASaver::save(const QQueue<QA> &questionAnswers)
{
    validateFile();
    std::shared_ptr<CanSerializeData> serializer = fileSerializerFactory->create(file.getIODevice());
    serializeFileVersion(*serializer);

    foreach(QA qA, questionAnswers)
        serializeQA(*serializer, qA);

    return serializer->status()==QDataStream::Ok;
}
