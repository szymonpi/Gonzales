#ifndef QASAVER_H
#define QASAVER_H
#include <memory>

#include "qacontainer.h"
#include "../common/qtproxies/file.h"
#include "../common/qtproxies/filefactory.h"
#include "../common/qtproxies/fileserializerfactory.h"
#include "../common/common.h"
#include "../Common/simpletree.h"
class QASaver
{
public:

    QASaver(std::shared_ptr<IFileFactory> fileFactory = std::make_shared<FileFactory>(),
            std::shared_ptr<IFileSerializerFactory> fileSerializerFactory = std::make_shared<FileSerializerFactory>());

    void save(const Node<QA> &QuestionAnswers, const QString &filePath);

private:


    std::shared_ptr<IFileFactory> fileFactory;
    std::shared_ptr<IFileSerializerFactory> fileSerializerFactory;
    void openFile(ReadableWritableFile &file);
    void serializeFileVersion(CanSerializeData &serializer);
    void serializeQA(CanSerializeData &serializer, const QA &qa) const;
};

#endif // QASAVER_H
