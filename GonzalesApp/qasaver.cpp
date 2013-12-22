#include "qasaver.h"

QASaver::QASaver(ReadableWritableFile &file, std::shared_ptr<IFileSerializerFactory> fileSerializerFactory):
    file(file),
    fileSerializerFactory(fileSerializerFactory)
{
}

bool QASaver::save(const QA &QuestionAnswerObject)
{
    if(!file.isOpen())
        throw FileException("File isn't open");
    if(!file.isWritable())
        throw FileException("File isn't writable");

    std::shared_ptr<CanSerializeData> fileSerializer = fileSerializerFactory->create(file.getIODevice());

    std::string question= QuestionAnswerObject.question.geAstString();
    std::string answer= QuestionAnswerObject.answer.getAsString();

    fileSerializer->serialize(static_cast<quint16>(FileVersion::QAFileVersion1));
    fileSerializer->serialize(question.c_str());
    fileSerializer->serialize(answer.c_str());
    return fileSerializer->status()==QDataStream::Ok;
}
