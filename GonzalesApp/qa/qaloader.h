#ifndef QALOADER_H
#define QALOADER_H

#include <memory>

#include<QQueue>

#include "qacontainer.h"
#include "../common/qtproxies/file.h"
#include "../common/qtproxies/filedeserializerfactory.h"
#include "../common/qtproxies/filefactory.h"
#include "../common/common.h"
#include "../Common/SimpleTree/Node.h"
#include "QASerializer.h"

class IQALoader
{
public:
    virtual SimpleTree::Node<QA> load(const QString &userName) = 0;
    ~IQALoader(){}
};

class QALoader: public IQALoader
{
public:
    QALoader(std::shared_ptr<IFileFactory> fileFactory = std::make_shared<FileFactory>(),
            std::shared_ptr<IQADeserializer> qADeserializer = std::make_shared<QASerializer>(),
             std::shared_ptr<IFileDeserializerFactory> fileDeserializerFactory
                = std::make_shared<FileDeserializerFactory>());

    SimpleTree::Node<QA> load(const QString &userName);

private:
    std::shared_ptr<IFileFactory> m_fileFactory;
    std::shared_ptr<IQADeserializer> m_qADeserializer;
    std::shared_ptr<IFileDeserializerFactory> m_fileDeserializerFactory;

    void checkFileVersion(CanDeserializeData &deserializer);
    void validateDeserializerStatus(CanDeserializeData &deserializer);
    std::shared_ptr<QA> getDeserializedQA(CanDeserializeData &deserializer);
    void addProperlyDeserializedQA(CanDeserializeData &deserializer, SimpleTree::Node<QA> &queue);
};


#endif // QALOADER_H
