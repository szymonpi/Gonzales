#include "QALoader.h"
#include <memory>
#include "../../common/SimpleTree/Utils.h"

QALoader::QALoader(std::shared_ptr<IQAsFilePathProvider> filePathProvider,
                   std::shared_ptr<IFileFactory> fileFactory,
                   std::shared_ptr<IQADeserializer> qASerializer,
                   std::shared_ptr<IDataDeserializerFactory> dataDeserializerFactory):
    m_filePathProvider(filePathProvider),
    m_fileFactory(fileFactory),
    m_qADeserializer(qASerializer),
    m_DataDeserializerFactory(dataDeserializerFactory)
{
}

void QALoader::checkFileVersion(IDataDeserializer &deserializer)
{
    quint16 fileVersion=0;
    deserializer.deserialize(fileVersion);

    if(fileVersion != QAFileVersion1)
        throw FileException("unsupported file version");
}

void QALoader::validateDeserializerStatus(IDataDeserializer &deserializer)
{

    if(deserializer.status()==QDataStream::ReadCorruptData)
        throw FileException("corrupted data");

}

SimpleTree::Node<QA> QALoader::load()
{
    std::shared_ptr<IFile> file = m_fileFactory->create(m_filePathProvider->getPath());
    if(!file->open(QFile::ReadOnly))
        throw FileException("Can't open file");

    std::shared_ptr<IDataDeserializer> deserializer = m_DataDeserializerFactory->create(file->getIODevice());
    checkFileVersion(*deserializer);

    SimpleTree::Node<QA> qAs;
    m_qADeserializer->deserialize(*deserializer, qAs);
    validateDeserializerStatus(*deserializer);
    return qAs;
}
