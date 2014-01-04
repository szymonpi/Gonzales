#ifndef QASAVER_H
#define QASAVER_H
#include <memory>

#include "qacontainer.h"
#include "../file/file.h"
#include "../file/filefactory.h"
#include "../file/fileserializerfactory.h"
#include "../common/common.h"
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
