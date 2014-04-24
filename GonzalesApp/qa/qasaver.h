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

    void save(const std::vector<Node<QA> > &QuestionAnswers, const QString &filePath);

private:


    std::shared_ptr<IFileFactory> fileFactory;
    std::shared_ptr<IFileSerializerFactory> fileSerializerFactory;
    void openFile(ReadableWritableFile &file);
    void serializeFileVersion(CanSerializeData &serializer);
};

#endif // QASAVER_H
