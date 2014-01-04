#include "qaloader.h"


void QALoader::validateFile()
{
    if(!file.isOpen())
        throw FileException("File isn't open");
    if(!file.isReadable())
        throw FileException("File isn't readable");
}

void QALoader::checkfileVersion(CanDeserializeData &deserializer)
{
    quint16 fileVersion=0;
    deserializer.deserialize(fileVersion);

    if(fileVersion != QAFileVersion1)
        throw std::logic_error("unsupported file version");
}

void QALoader::validateDeserializerStatus(CanDeserializeData &deserializer)
{
    if(deserializer.status() != QDataStream::Ok)
    {
        if(deserializer.status()==QDataStream::ReadCorruptData)
            throw FileException("corrupted data");
        else if(deserializer.status()==QDataStream::ReadPastEnd)
            throw FileException("empty file or can't read answer");
    }
}

QA QALoader::getDeserializedQA(CanDeserializeData &deserializer)
{
    char *question;
    char *answer;

    deserializer.deserialize(question);
    deserializer.deserialize(answer);

    return QA(Question(question), Answer(answer));
}

void QALoader::addProperlyDeserializedQA(CanDeserializeData &deserializer, QQueue<QA> &queue)
{
    queue.append(getDeserializedQA(deserializer));
    validateDeserializerStatus(deserializer);
}

QQueue<QA> QALoader::load()
{
    validateFile();
    std::shared_ptr<CanDeserializeData> deserializer = fileDeserializerFactory->create(file.getIODevice());
    checkfileVersion(*deserializer);

    QQueue<QA> qAs;
    while(!deserializer->atEnd())
        addProperlyDeserializedQA(*deserializer, qAs);

    return qAs;
}
