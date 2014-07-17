#include <iostream>
#include <memory>

#include "../gtest.h"
#include "../gmock.h"

#include <QQueue>

#include "../../GonzalesApp/qa/qaio/QALoader.h"

#include "DataDeserializerMock.h"
#include "DataDeserializerFactoryMock.h"
#include "FileMock.h"
#include "QASerializerMock.h"
#include "QAsFilePathProviderMock.h"

using namespace testing;

class QALoadTestSuite : public testing::Test
{
protected:
    QALoadTestSuite():
        filePathProviderMock(std::make_shared<QAsFilePathProviderMock>()),
        fileMock(std::make_shared<FileMock>()),
        fileFactoryMock(std::make_shared<FileFactoryMock>()),
        dataDeserializerMock(std::make_shared<DataDeserializerMock>()),
        dataDeserializerFactoryMock(std::make_shared<DataDeserializerFactoryMock>()),
        loader(filePathProviderMock, fileFactoryMock, m_qaDeserializerMock, dataDeserializerFactoryMock),
        qa(Question("question"), Answer("answer"))
    {
        EXPECT_CALL(*filePathProviderMock, getPath()).WillOnce(Return(path));
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
        EXPECT_CALL(*dataDeserializerFactoryMock, create(_)).WillOnce(Return(dataDeserializerMock));
    }

    void expectDeserializeFileVersion(QAFileVersion version)
    {
        EXPECT_CALL(*dataDeserializerMock, deserialize(An<quint16&>()))
                        .WillOnce(SetArgReferee<0>(static_cast<quint16>(version)));
    }

    void expectDeserializeQAs()
    {
        EXPECT_CALL(*m_qaDeserializerMock, deserialize(_,_));
    }

    void expectDeserializedDataWillBeCorupted()
    {
        EXPECT_CALL(*dataDeserializerMock, status()).WillOnce(Return(QDataStream::ReadCorruptData));
    }

    QString path = "path";
    std::shared_ptr<QAsFilePathProviderMock> filePathProviderMock;
    std::shared_ptr<FileMock> fileMock;
    std::shared_ptr<FileFactoryMock> fileFactoryMock;
    std::shared_ptr<DataDeserializerMock> dataDeserializerMock;
    std::shared_ptr<DataDeserializerFactoryMock> dataDeserializerFactoryMock;
    std::shared_ptr<QADeserializerMock> m_qaDeserializerMock = std::make_shared<QADeserializerMock>();
    QALoader loader;
    QQueue<QA> qAs;
    QA qa;

};

TEST_F(QALoadTestSuite, shouldntLoadFile_FileIsntOpen)
{
    expectOpenFile(false);
    ASSERT_THROW(loader.load(), FileException);
}

TEST_F(QALoadTestSuite, shouldntLoadAnyQA_FileVersionIsUnsupported)
{
    expectFileIsReadyToRead();
    expectCreateDeserializer();
    expectDeserializeFileVersion(QAUnsupportedFileVersion);
    EXPECT_THROW(loader.load(), FileException);
}

TEST_F(QALoadTestSuite, shouldntImportAnyQA_DataCorupted)
{
    expectFileIsReadyToRead();
    expectCreateDeserializer();
    expectDeserializeFileVersion(QAFileVersion1);
    expectDeserializeQAs();
    expectDeserializedDataWillBeCorupted();

    EXPECT_THROW(loader.load(), FileException);
}

TEST_F(QALoadTestSuite, shouldLoadQAsFromFile)
{
    expectFileIsReadyToRead();
    expectCreateDeserializer();
    expectDeserializeFileVersion(QAFileVersion1);

    std::shared_ptr<QA> qa = std::make_shared<QA>(Question("question"), Answer("answer"));
    SimpleTree::Node<QA> rootNodeToSet(qa);
    EXPECT_CALL(*m_qaDeserializerMock, deserialize(_,_)).WillOnce(SetArgReferee<1>(rootNodeToSet));
    EXPECT_CALL(*dataDeserializerMock, status()).WillOnce(Return(QDataStream::Ok));

    SimpleTree::Node<QA> rootNode = loader.load();
    EXPECT_EQ(rootNode, rootNodeToSet);
}
