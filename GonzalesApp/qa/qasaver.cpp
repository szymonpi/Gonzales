#include <QQueue>

#include "qasaver.h"
#include "../Common/SimpleTree/Node.h"
#include "../Common/SimpleTree/Utils.h"


QASaver::QASaver(std::shared_ptr<IFileFactory> fileFactory,
                 std::shared_ptr<IQASerializer> qASerializer,
                 std::shared_ptr<IDataSerializerFactory> dataSerializerFactory):
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

void QASaver::save(const SimpleTree::Node<QA> &questionAnswers, const QString &filePath)
{
    std::shared_ptr<IFile> file = fileFactory->create(filePath);
    openFile(*file);
    std::shared_ptr<IDataSerializer> serializer = dataSerializerFactory->create(file->getIODevice());
    serializeFileVersion(*serializer);

    qASerializer->serialize(*serializer, questionAnswers);

    if(serializer->status()!=QDataStream::Ok)
        throw FileException("Something wen't wrong when saving file");
}
