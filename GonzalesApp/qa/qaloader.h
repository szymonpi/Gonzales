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

    QQueue<QA> load();

private:
    ReadableWritableFile &file;
    std::shared_ptr<IFileDeserializerFactory> fileDeserializerFactory;

    void validateFile();
    void checkfileVersion(CanDeserializeData &deserializer);
    void validateDeserializerStatus(CanDeserializeData &deserializer);
    QA getDeserializedQA(CanDeserializeData &deserializer);
    void addProperlyDeserializedQA(CanDeserializeData &deserializer, QQueue<QA> &queue);
};


#endif // QALOADER_H
