#include "qaloader.h"
#include <memory>
#include "../Common/SimpleTree/utils.h"

QALoader::QALoader(std::shared_ptr<IFileFactory> fileFactory,
                   std::shared_ptr<IQADeserializer> qADeserializer,
                   std::shared_ptr<IFileDeserializerFactory> fileDeserializerFactory):
    m_fileFactory(fileFactory),
    m_qADeserializer(qADeserializer),
    m_fileDeserializerFactory(fileDeserializerFactory)
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


std::vector<SimpleTree::Node<QA>> QALoader::load(const QString &userName)
{
    QString filePath = getFilePathToQas(userName);
    std::shared_ptr<ReadableWritableFile> file = m_fileFactory->create(filePath);
    if(!file->open(QFile::ReadOnly))
        throw FileException("Can't open file");

    std::shared_ptr<CanDeserializeData> deserializer = m_fileDeserializerFactory->create(file->getIODevice());
    checkFileVersion(*deserializer);

    std::vector<SimpleTree::Node<QA>> qAs;
    m_qADeserializer->deserialize(*deserializer, qAs.at(0));
    validateDeserializerStatus(*deserializer);
    return qAs;
}
