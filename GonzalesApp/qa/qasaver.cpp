#include <QQueue>

#include "qasaver.h"
#include "../Common/SimpleTree/node.h"
#include "../Common/SimpleTree/utils.h"


QASaver::QASaver(std::shared_ptr<IFileFactory> fileFactory,
                 std::shared_ptr<IQASerializer> qASerializer,
                 std::shared_ptr<IFileSerializerFactory> fileSerializerFactory):
    fileFactory(fileFactory),
    qASerializer(qASerializer),
    fileSerializerFactory(fileSerializerFactory)
{
}

void QASaver::openFile(IFile &file)
{
    if(!file.open(QFile::WriteOnly))
        throw FileException("File isn't open");
}

void QASaver::serializeFileVersion(CanSerializeData &serializer)
{
    serializer.serialize(static_cast<quint16>(QAFileVersion1));
}

void QASaver::save(const SimpleTree::Node<QA> &questionAnswers, const QString &filePath)
{
    std::shared_ptr<IFile> file = fileFactory->create(filePath);
    openFile(*file);
    std::shared_ptr<CanSerializeData> serializer = fileSerializerFactory->create(file->getIODevice());
    serializeFileVersion(*serializer);

    qASerializer->serialize(*serializer, questionAnswers);

    if(serializer->status()!=QDataStream::Ok)
        throw FileException("Something wen't wrong when saving file");
}
