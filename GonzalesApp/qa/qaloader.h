#ifndef QALOADER_H
#define QALOADER_H

#include <memory>

#include<QQueue>

#include "qacontainer.h"
#include "../common/qtproxies/file.h"
#include "../common/qtproxies/filedeserializerfactory.h"
#include "../common/qtproxies/filefactory.h"
#include "../common/common.h"

class QALoader
{
public:
    QALoader(std::shared_ptr<IFileFactory> fileFactory = std::make_shared<FileFactory>(),
            std::shared_ptr<IFileDeserializerFactory> fileSerializerFactory = std::make_shared<FileDeserializerFactory>());

    QQueue<QA> load(const QString &filePath);

private:
    std::shared_ptr<IFileFactory> m_fileFactory;
    std::shared_ptr<IFileDeserializerFactory> m_fileDeserializerFactory;

    void checkFileVersion(CanDeserializeData &deserializer);
    void validateDeserializerStatus(CanDeserializeData &deserializer);
    QA getDeserializedQA(CanDeserializeData &deserializer);
    void addProperlyDeserializedQA(CanDeserializeData &deserializer, QQueue<QA> &queue);
};


#endif // QALOADER_H
