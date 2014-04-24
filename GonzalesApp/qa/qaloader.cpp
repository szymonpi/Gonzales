#include "qaloader.h"
#include <memory>

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

std::shared_ptr<QA> QALoader::getDeserializedQA(CanDeserializeData &deserializer)
{
    Question q("");
    q.deserialize(deserializer);

    Answer a("");
    a.deserialize(deserializer);

    return std::make_shared<QA>(q,a);
}

void QALoader::addProperlyDeserializedQA(CanDeserializeData &deserializer, Node<QA> &node)
{
    node.appendNodeValue(getDeserializedQA(deserializer));

}


std::vector<Node<QA>> QALoader::load(const QString &userName)
{
    QString filePath = getFilePathToQas(userName);
    std::shared_ptr<ReadableWritableFile> file = m_fileFactory->create(filePath);
    if(!file->open(QFile::ReadOnly))
        throw FileException("Can't open file");

    std::shared_ptr<CanDeserializeData> deserializer = m_fileDeserializerFactory->create(file->getIODevice());
    checkFileVersion(*deserializer);

    std::vector<Node<QA>> qAs;
    Node<QA>::deserialize(qAs, *deserializer);
    validateDeserializerStatus(*deserializer);
    return qAs;
}
