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
    Question q("");
    q.deserialize(deserializer);

    Answer a("");
    a.deserialize(deserializer);

    QA qa(q, a);

    return qa;
}

void QALoader::addProperlyDeserializedQA(CanDeserializeData &deserializer, std::vector<QA> &queue)
{
    queue.push_back(getDeserializedQA(deserializer));
    validateDeserializerStatus(deserializer);
}


std::vector<QA> QALoader::load(const QString &userName)
{
    QString filePath = getFilePathToQas(userName);
    std::shared_ptr<ReadableWritableFile> file = m_fileFactory->create(filePath);
    if(!file->open(QFile::ReadOnly))
        throw FileException("Can't open file");

    std::shared_ptr<CanDeserializeData> deserializer = m_fileDeserializerFactory->create(file->getIODevice());
    checkFileVersion(*deserializer);

    std::vector<QA> qAs;
    while(!deserializer->atEnd())
        addProperlyDeserializedQA(*deserializer, qAs);

    return qAs;
}
