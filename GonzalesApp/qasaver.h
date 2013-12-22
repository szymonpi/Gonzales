#ifndef QASAVER_H
#define QASAVER_H
#include <memory>

#include "fileoperations/file.h"
#include "qacontainer.h"
#include "fileoperations/filefactory.h"
#include "fileoperations/fileserializerfactory.h"
class QASaver
{
public:
    enum FileVersion
    {
        QAFileVersion1 = 0
    };

    QASaver(ReadableWritableFile &file,
            std::shared_ptr<IFileSerializerFactory> fileSerializerFactory = std::make_shared<FileSerializerFactory>());

    bool save(const QA &QuestionAnswerObject);

private:


    ReadableWritableFile &file;
    std::shared_ptr<IFileSerializerFactory> fileSerializerFactory;
};

#endif // QASAVER_H
