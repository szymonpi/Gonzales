#ifndef QASAVER_H
#define QASAVER_H
#include <memory>

#include "fileoperations/file.h"
#include "qacontainer.h"
#include "fileoperations/filefactory.h"
#include "fileoperations/fileserializerfactory.h"
#include "common.h"
class QASaver
{
public:

    QASaver(ReadableWritableFile &file,
            std::shared_ptr<IFileSerializerFactory> fileSerializerFactory = std::make_shared<FileSerializerFactory>());

    bool save(const QQueue<QA> &QuestionAnswers);

private:


    ReadableWritableFile &file;
    std::shared_ptr<IFileSerializerFactory> fileSerializerFactory;
};

#endif // QASAVER_H
