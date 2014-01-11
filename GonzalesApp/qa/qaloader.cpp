#include "qaloader.h"

QALoader::QALoader(std::shared_ptr<IFileFactory> fileFactory,
                   std::shared_ptr<IFileDeserializerFactory> fileSerializerFactory):
    m_fileFactory(fileFactory),
    m_fileDeserializerFactory(fileSerializerFactory)
{
}

void QALoader::checkFileVersion(CanDeserializeData &deserializer)
{
    quint16 fileVersion=0;
    deserializer.deserialize(fileVersion);

    if(fileVersion != QAFileVersion1)
        throw FileException("unsupported file version");
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


QQueue<QA> QALoader::load(const QString &filePath)
{
    std::shared_ptr<ReadableWritableFile> file = m_fileFactory->create(filePath);
    if(!file->open(QFile::ReadOnly))
        throw FileException("Can't open file");

    std::shared_ptr<CanDeserializeData> deserializer = m_fileDeserializerFactory->create(file->getIODevice());
    checkFileVersion(*deserializer);

    QQueue<QA> qAs;
    while(!deserializer->atEnd())
        addProperlyDeserializedQA(*deserializer, qAs);

    return qAs;
}
