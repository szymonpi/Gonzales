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

void QASaver::openFile(ReadableWritableFile &file)
{
    if(!file.open(QFile::WriteOnly))
        throw FileException("File isn't open");
}

void QASaver::serializeFileVersion(CanSerializeData &serializer)
{
    serializer.serialize(static_cast<quint16>(QAFileVersion1));
}

void QASaver::save(const std::vector<SimpleTree::Node<QA> > &questionAnswers, const QString &userName)
{
    QString fileName = getFilePathToQas(userName);
    std::shared_ptr<ReadableWritableFile> file = fileFactory->create(fileName);
    openFile(*file);
    std::shared_ptr<CanSerializeData> serializer = fileSerializerFactory->create(file->getIODevice());
    serializeFileVersion(*serializer);

    for(auto it = questionAnswers.begin(); it!=questionAnswers.end(); it++)
    {
        qASerializer->serialize(*serializer, *it);
    }

    if(serializer->status()!=QDataStream::Ok)
        throw FileException("Something wen't wrong when saving file");
}
