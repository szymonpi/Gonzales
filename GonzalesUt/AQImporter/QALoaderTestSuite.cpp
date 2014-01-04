#include <iostream>
#include <memory>

#include "../gtest.h"
#include "../gmock.h"

#include <QQueue>

#include "../../GonzalesApp/qa/qaloader.h"

#include "FileDeserializerMock.h"
#include "FileDeserializerFactoryMock.h"
#include "FileMock.h"

using namespace testing;

class QALoadTestSuite : public testing::Test
{
protected:
    QALoadTestSuite():
        fileMock(),
        fileDeserializerMock(std::make_shared<FileDeserializerMock>()),
        fileDeserializerFactoryMock(std::make_shared<FileDeserializerFactoryMock>()),
        loader(fileMock, fileDeserializerFactoryMock),
        qa(Question("question"), Answer("answer"))
    {
    }

    void SetUp()
    {
        qAs.append(qa);
    }


    void expectFileIsReadyToRead()
    {
        QFile device;
        expectFileIsReadable(true);
        EXPECT_CALL(fileMock, getIODevice()).WillOnce(Return(&device));
    }

    void expectFileIsOpen(bool open)
    {
        EXPECT_CALL(fileMock, isOpen()).WillOnce(Return(open));
    }

    void expectFileIsReadable(bool readable)
    {
        expectFileIsOpen(true);
        EXPECT_CALL(fileMock, isReadable()).WillOnce(Return(readable));
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

    void expectDeserializeQuestionAndAnswer()
    {
        char *question = const_cast<char *>(qa.question.getAsString().c_str());
        char *answer = const_cast<char *>(qa.answer.getAsString().c_str());

        EXPECT_CALL(*fileDeserializerMock, deserialize(An<char *&>()))
                .WillOnce(SetArgReferee<0>(question))
                .WillOnce(SetArgReferee<0>(answer));
    }

    void expectDeserializedDataWillBeCorupted()
    {
        EXPECT_CALL(*fileDeserializerMock, status()).WillOnce(Return(QDataStream::ReadCorruptData))
                                                    .WillOnce(Return(QDataStream::ReadCorruptData));
    }

    void expectDeserializerPastEndToQuickly()
    {
        EXPECT_CALL(*fileDeserializerMock, status()).WillOnce(Return(QDataStream::ReadPastEnd))
                                                    .WillOnce(Return(QDataStream::ReadPastEnd))
                                                    .WillOnce(Return(QDataStream::ReadPastEnd));
    }

    void expectDeserializerInvokeOneLoop()
    {
        EXPECT_CALL(*fileDeserializerMock, atEnd()).WillOnce(Return(false))
                                                 .WillOnce(Return(true));
    }

    void expectDeserializerInvokeNoLoop()
    {
        EXPECT_CALL(*fileDeserializerMock, atEnd()).WillOnce(Return(true));
    }

    void expectDeserializerInvokeOneUnfinishedLoop()
    {
        EXPECT_CALL(*fileDeserializerMock, atEnd()).WillOnce(Return(false));
    }

    FileMock fileMock;
    std::shared_ptr<FileDeserializerMock> fileDeserializerMock;
    std::shared_ptr<FileDeserializerFactoryMock> fileDeserializerFactoryMock;
    QALoader loader;
    QQueue<QA> qAs;
    QA qa;

};



TEST_F(QALoadTestSuite, shouldntLoadFile_FileIsntOpen)
{
    expectFileIsOpen(false);
    ASSERT_THROW(loader.load(), FileException);
}

TEST_F(QALoadTestSuite, shouldntLoadFile_FileIsntReadable)
{
    expectFileIsReadable(false);
    ASSERT_THROW(loader.load(), FileException);
}

TEST_F(QALoadTestSuite, shouldntLoadAnyQA_FileVersionIsUnsupported)
{
    expectFileIsReadyToRead();
    expectCreateDeserializer();
    expectDeserializeFileVersion(QAUnsupportedFileVersion);
    EXPECT_THROW(loader.load(), std::logic_error);

}

TEST_F(QALoadTestSuite, shouldntImportAnyQA_DataCorupted)
{
    expectFileIsReadyToRead();
    expectCreateDeserializer();
    expectDeserializeFileVersion(QAFileVersion1);
    expectDeserializerInvokeOneUnfinishedLoop();
    expectDeserializeQuestionAndAnswer();
    expectDeserializedDataWillBeCorupted();

    EXPECT_THROW(loader.load(), FileException);
}

TEST_F(QALoadTestSuite, shouldntImportAnyQA_ReadPastEnd)
{
    expectFileIsReadyToRead();
    expectCreateDeserializer();
    expectDeserializeFileVersion(QAFileVersion1);
    expectDeserializerInvokeOneUnfinishedLoop();
    expectDeserializeQuestionAndAnswer();
    expectDeserializerPastEndToQuickly();

    EXPECT_THROW(loader.load(), FileException);
}

TEST_F(QALoadTestSuite, shouldntImportAnyQA_EmptyQAFile)
{
    expectFileIsReadyToRead();
    expectCreateDeserializer();
    expectDeserializeFileVersion(QAFileVersion1);
    expectDeserializerInvokeNoLoop();

    EXPECT_TRUE(loader.load().isEmpty());
}

TEST_F(QALoadTestSuite, shouldLoadOneQaFromFile)
{
    expectFileIsReadyToRead();
    expectCreateDeserializer();
    expectDeserializeFileVersion(QAFileVersion1);
    expectDeserializeQuestionAndAnswer();
    expectDeserializerInvokeOneLoop();
    EXPECT_CALL(*fileDeserializerMock, status()).WillOnce(Return(QDataStream::Ok));

    QQueue<QA> qAs = loader.load();
    ASSERT_FALSE(qAs.isEmpty());
    QA importedQa = qAs.first();
    EXPECT_EQ(qa, importedQa);

}

