#pragma once
#include <memory>

#include "QA.h"
#include "../common/qtproxies/File.h"
#include "../common/qtproxies/FileFactory.h"
#include "../common/qtproxies/DataSerializerFactory.h"
#include "../common/Common.h"
#include "../common/SimpleTree/Node.h"
#include "QASerializer.h"
#include "IQASaver.h"
#include "IQAsFilePathProvider.h"

class QASaver : public IQASaver
{
public:

    QASaver(std::shared_ptr<IQAsFilePathProvider> filePathProvider,
            std::shared_ptr<IFileFactory> fileFactory = std::make_shared<FileFactory>(),
            std::shared_ptr<IQASerializer> qASerializer = std::make_shared<QASerializer>(),
            std::shared_ptr<IDataSerializerFactory> dataSerializerFactory =
                std::make_shared<DataSerializerFactory>());

    void save(const SimpleTree::Node<QA> &QuestionAnswers) override;

private:

    std::shared_ptr<IQAsFilePathProvider> m_filePathProvider;
    std::shared_ptr<IFileFactory> fileFactory;
    std::shared_ptr<IQASerializer> qASerializer;
    std::shared_ptr<IDataSerializerFactory> dataSerializerFactory;
    void openFile(IFile &file);
    void serializeFileVersion(IDataSerializer &serializer);
};

