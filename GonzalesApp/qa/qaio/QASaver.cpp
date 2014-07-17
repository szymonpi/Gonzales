#include <QQueue>

#include "QASaver.h"
#include "../../common/SimpleTree/Node.h"
#include "../../common/SimpleTree/Utils.h"


QASaver::QASaver(std::shared_ptr<IQAsFilePathProvider> filePathProvider,
                 std::shared_ptr<IFileFactory> fileFactory,
                 std::shared_ptr<IQASerializer> qASerializer,
                 std::shared_ptr<IDataSerializerFactory> dataSerializerFactory):
    m_filePathProvider(filePathProvider),
    fileFactory(fileFactory),
    qASerializer(qASerializer),
    dataSerializerFactory(dataSerializerFactory)
{
}

void QASaver::openFile(IFile &file)
{
    if(!file.open(QFile::WriteOnly))
        throw FileException("File isn't open");
}

void QASaver::serializeFileVersion(IDataSerializer &serializer)
{
    serializer.serialize(static_cast<quint16>(QAFileVersion1));
}

void QASaver::save(const SimpleTree::Node<QA> &questionAnswers)
{
    std::shared_ptr<IFile> file = fileFactory->create(m_filePathProvider->getPath());
    openFile(*file);
    std::shared_ptr<IDataSerializer> serializer = dataSerializerFactory->create(file->getIODevice());
    serializeFileVersion(*serializer);

    qASerializer->serialize(*serializer, questionAnswers);

    if(serializer->status()!=QDataStream::Ok)
        throw FileException("Something wen't wrong when saving file");
}
