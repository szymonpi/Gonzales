#pragma once
#include <memory>

#include "qacontainer.h"
#include "../common/qtproxies/file.h"
#include "../common/qtproxies/filefactory.h"
#include "../common/qtproxies/fileserializerfactory.h"
#include "../common/common.h"
#include "../Common/SimpleTree/Node.h"
#include "QASerializer.h"

class QASaver
{
public:

    QASaver(std::shared_ptr<IFileFactory> fileFactory = std::make_shared<FileFactory>(),
            std::shared_ptr<IQASerializer> qASerializer = std::make_shared<QASerializer>(),
            std::shared_ptr<IFileSerializerFactory> fileSerializerFactory =
                std::make_shared<FileSerializerFactory>());

    void save(const SimpleTree::Node<QA> &QuestionAnswers, const QString &path);

private:


    std::shared_ptr<IFileFactory> fileFactory;
    std::shared_ptr<IQASerializer> qASerializer;
    std::shared_ptr<IFileSerializerFactory> fileSerializerFactory;
    void openFile(IFile &file);
    void serializeFileVersion(CanSerializeData &serializer);
};

