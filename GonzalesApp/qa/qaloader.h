#ifndef QALOADER_H
#define QALOADER_H

#include <memory>

#include<QQueue>

#include "qacontainer.h"
#include "../file/file.h"
#include "../file/filedeserializerfactory.h"
#include "../common/common.h"

class QALoader
{
public:
    QALoader(ReadableWritableFile &file,
            std::shared_ptr<IFileDeserializerFactory> fileSerializerFactory = std::make_shared<FileDeserializerFactory>()):
        file(file),
        fileDeserializerFactory(fileSerializerFactory)
    {

    }

    QQueue<QA> load()
    {
        if(!file.isOpen())
            throw FileException("File isn't open");
        if(!file.isReadable())
            throw FileException("File isn't readable");
        std::shared_ptr<CanDeserializeData> deserializer = fileDeserializerFactory->create(file.getIODevice());

        quint16 fileVersion=0;
        deserializer->deserialize(fileVersion);

        if(fileVersion != QAFileVersion1)
            throw std::logic_error("unsupported file version");

        QQueue<QA> qAs;
        while(!deserializer->atEnd())
        {
            char *question;
            char *answer;

            deserializer->deserialize(question);
            deserializer->deserialize(answer);

            if(deserializer->status() != QDataStream::Ok)
            {
                if(deserializer->status()==QDataStream::ReadCorruptData)
                    throw FileException("corrupted data");
                else if(deserializer->status()==QDataStream::ReadPastEnd)
                    throw FileException("empty file or can't read answer");
            }

            qAs.append(QA(Question(question), Answer(answer)));
        }

        if(qAs.isEmpty())
            throw FileException("Empty qa file");

        return qAs;
    }

private:
    ReadableWritableFile &file;
    std::shared_ptr<IFileDeserializerFactory> fileDeserializerFactory;

};


#endif // QALOADER_H
