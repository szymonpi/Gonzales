#include <iostream>
#include <memory>

#include "../gtest.h"
#include "../gmock.h"

#include <QQueue>

#include "../../GonzalesApp/qa/qaloader.h"

#include "FileDeserializerMock.h"
#include "FileDeserializerFactoryMock.h"
#include "FileMock.h"
#include "QASerializerMock.h"

using namespace testing;

class QALoadTestSuite : public testing::Test
{
protected:
    QALoadTestSuite():
        fileMock(std::make_shared<FileMock>()),
        fileFactoryMock(std::make_shared<FileFactoryMock>()),
        fileDeserializerMock(std::make_shared<FileDeserializerMock>()),
        fileDeserializerFactoryMock(std::make_shared<FileDeserializerFactoryMock>()),
        loader(fileFactoryMock, m_qaDeserializerMock, fileDeserializerFactoryMock),
        qa(Question("question"), Answer("answer"))
    {
    }

    void SetUp()
    {
        qAs.append(qa);
        EXPECT_CALL(*fileFactoryMock, create(path)).WillOnce(Return(fileMock));
    }


    void expectFileIsReadyToRead()
    {
        QFile device;
        expectOpenFile(true);
        EXPECT_CALL(*fileMock, getIODevice()).WillOnce(Return(&device));
    }

    void expectOpenFile(bool success)
    {
        EXPECT_CALL(*fileMock, open(_)).WillOnce(Return(success));
    }

    void expectCreateDeserializer()
    {
        EXPECT_CALL(*fileDeserializerFactoryMock, create(_)).WillOnce(Return(fileDeserializerMock));
    }

    void expectDeserializeFileVersion(QAFileVersion version)
    {
        EXPECT_CALL(*fileDeserializerMock, deserialize(An<quint16&>()))
                        .WillOnce(SetArgReferee<0>(static_cast<quint16>(version)));
    }

    void expectDeserializeQAs()
    {
        EXPECT_CALL(*m_qaDeserializerMock, deserialize(_,_));
    }

    void expectDeserializedDataWillBeCorupted()
    {
        EXPECT_CALL(*fileDeserializerMock, status()).WillOnce(Return(QDataStream::ReadCorruptData));
    }

    QString path = "path";
    std::shared_ptr<FileMock> fileMock;
    std::shared_ptr<FileFactoryMock> fileFactoryMock;
    std::shared_ptr<FileDeserializerMock> fileDeserializerMock;
    std::shared_ptr<FileDeserializerFactoryMock> fileDeserializerFactoryMock;
    std::shared_ptr<QADeserializerMock> m_qaDeserializerMock = std::make_shared<QADeserializerMock>();
    QALoader loader;
    QQueue<QA> qAs;
    QA qa;

};

TEST_F(QALoadTestSuite, shouldntLoadFile_FileIsntOpen)
{
    expectOpenFile(false);
    ASSERT_THROW(loader.load(path), FileException);
}

TEST_F(QALoadTestSuite, shouldntLoadAnyQA_FileVersionIsUnsupported)
{
    expectFileIsReadyToRead();
    expectCreateDeserializer();
    expectDeserializeFileVersion(QAUnsupportedFileVersion);
    EXPECT_THROW(loader.load(path), FileException);
}

TEST_F(QALoadTestSuite, shouldntImportAnyQA_DataCorupted)
{
    expectFileIsReadyToRead();
    expectCreateDeserializer();
    expectDeserializeFileVersion(QAFileVersion1);
    expectDeserializeQAs();
    expectDeserializedDataWillBeCorupted();

    EXPECT_THROW(loader.load(path), FileException);
}

TEST_F(QALoadTestSuite, shouldLoadQAsFromFile)
{
    expectFileIsReadyToRead();
    expectCreateDeserializer();
    expectDeserializeFileVersion(QAFileVersion1);

    std::shared_ptr<QA> qa = std::make_shared<QA>(Question("question"), Answer("answer"));
    SimpleTree::Node<QA> rootNodeToSet(qa);
    EXPECT_CALL(*m_qaDeserializerMock, deserialize(_,_)).WillOnce(SetArgReferee<1>(rootNodeToSet));
    EXPECT_CALL(*fileDeserializerMock, status()).WillOnce(Return(QDataStream::Ok));

    SimpleTree::Node<QA> rootNode = loader.load(path);
    EXPECT_EQ(rootNode, rootNodeToSet);
}
