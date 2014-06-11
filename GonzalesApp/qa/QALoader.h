#pragma once

#include <memory>
#include<QQueue>
#include "QA.h"
#include "../common/qtproxies/File.h"
#include "../common/qtproxies/DataDeserializerFactory.h"
#include "../common/qtproxies/FileFactory.h"
#include "../common/Common.h"
#include "../common/SimpleTree/Node.h"
#include "QASerializer.h"
#include "IQALoader.h"
#include "IQAsFilePathProvider.h"

class QALoader: public IQALoader
{
public:
    QALoader(std::shared_ptr<IQAsFilePathProvider> filePathProvider,
             std::shared_ptr<IFileFactory> fileFactory = std::make_shared<FileFactory>(),
             std::shared_ptr<IQADeserializer> qASerializer = std::make_shared<QASerializer>(),
             std::shared_ptr<IDataDeserializerFactory> dataDeserializerFactory
                = std::make_shared<DataDeserializerFactory>());

    SimpleTree::Node<QA> load();

private:
    std::shared_ptr<IQAsFilePathProvider> m_filePathProvider;
    std::shared_ptr<IFileFactory> m_fileFactory;
    std::shared_ptr<IQADeserializer> m_qADeserializer;
    std::shared_ptr<IDataDeserializerFactory> m_DataDeserializerFactory;

    void checkFileVersion(IDataDeserializer&deserializer);
    void validateDeserializerStatus(IDataDeserializer&deserializer);
    std::shared_ptr<QA> getDeserializedQA(IDataDeserializer&deserializer);
    void addProperlyDeserializedQA(IDataDeserializer&deserializer, SimpleTree::Node<QA> &queue);
};
