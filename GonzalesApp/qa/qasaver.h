#pragma once
#include <memory>

#include "qacontainer.h"
#include "../common/qtproxies/file.h"
#include "../common/qtproxies/filefactory.h"
#include "../common/qtproxies/DataSerializerFactory.h"
#include "../common/common.h"
#include "../Common/SimpleTree/Node.h"
#include "QASerializer.h"

class QASaver
{
public:

    QASaver(std::shared_ptr<IFileFactory> fileFactory = std::make_shared<FileFactory>(),
            std::shared_ptr<IQASerializer> qASerializer = std::make_shared<QASerializer>(),
            std::shared_ptr<IDataSerializerFactory> dataSerializerFactory =
                std::make_shared<DataSerializerFactory>());

    void save(const SimpleTree::Node<QA> &QuestionAnswers, const QString &path);

private:


    std::shared_ptr<IFileFactory> fileFactory;
    std::shared_ptr<IQASerializer> qASerializer;
    std::shared_ptr<IDataSerializerFactory> dataSerializerFactory;
    void openFile(IFile &file);
    void serializeFileVersion(IDataSerializer &serializer);
};

