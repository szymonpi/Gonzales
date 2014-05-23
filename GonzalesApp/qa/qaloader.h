#pragma once

#include <memory>

#include<QQueue>

#include "qacontainer.h"
#include "../common/qtproxies/file.h"
#include "../common/qtproxies/DataDeserializerfactory.h"
#include "../common/qtproxies/filefactory.h"
#include "../common/common.h"
#include "../Common/SimpleTree/Node.h"
#include "QASerializer.h"
#include "IQALoader.h"

class QALoader: public IQALoader
{
public:
    QALoader(std::shared_ptr<IFileFactory> fileFactory = std::make_shared<FileFactory>(),
             std::shared_ptr<IQADeserializer> qASerializer = std::make_shared<QASerializer>(),
             std::shared_ptr<IDataDeserializerFactory> DataDeserializerFactory
                = std::make_shared<DataDeserializerFactory>());

    SimpleTree::Node<QA> load(const QString &userName);

private:
    std::shared_ptr<IFileFactory> m_fileFactory;
    std::shared_ptr<IQADeserializer> m_qADeserializer;
    std::shared_ptr<IDataDeserializerFactory> m_DataDeserializerFactory;

    void checkFileVersion(IDataDeserializer&deserializer);
    void validateDeserializerStatus(IDataDeserializer&deserializer);
    std::shared_ptr<QA> getDeserializedQA(IDataDeserializer&deserializer);
    void addProperlyDeserializedQA(IDataDeserializer&deserializer, SimpleTree::Node<QA> &queue);
};
