#include <iostream>
#include <memory>

#include "../gtest.h"
#include "../gmock.h"

#include <QQueue>

#include "../../GonzalesApp/qasaver.h"
#include "FileSerializeMock.h"
#include "FileSerializerFactoryMock.h"
#include "FileMock.h"

using namespace testing;

class QASaveLoadTestSuite : public testing::Test
{
protected:
    QASaveLoadTestSuite():
        fileSerializerMock(std::make_shared<FileSerializerMock>()),
        fileSerializerFactoryMock(std::make_shared<FileSerializerFactoryMock>())
    {

    }

    std::shared_ptr<FileSerializerMock> fileSerializerMock;
    std::shared_ptr<FileSerializerFactoryMock> fileSerializerFactoryMock;
    FileMock fileMock;

};

TEST_F(QASaveLoadTestSuite, shouldSaveFile)
{
    QFile file;
    EXPECT_CALL(*fileSerializerFactoryMock, create(_)).WillOnce(Return(fileSerializerMock));
    EXPECT_CALL(fileMock, getIODevice()).WillOnce(Return(&file));
    EXPECT_CALL(fileMock, isOpen()).WillOnce(Return(true));
    EXPECT_CALL(fileMock, isWritable()).WillOnce(Return(true));

    quint16 version = static_cast<quint16>(QASaver::QAFileVersion1);
    std::string question = "question";
    std::string answer = "answer";

    EXPECT_CALL(*fileSerializerMock, serialize(Matcher<quint16>(version)));
    EXPECT_CALL(*fileSerializerMock, serialize(Matcher<const char *>(StrEq(question.c_str()))));
    EXPECT_CALL(*fileSerializerMock, serialize(Matcher<const char*>(StrEq(answer.c_str()))));
    EXPECT_CALL(*fileSerializerMock, status()).WillOnce(Return(QDataStream::Ok));

    QASaver saver(fileMock, fileSerializerFactoryMock);
    ASSERT_TRUE(saver.save(QA(Question("question"), Answer("answer"))));
}

TEST_F(QASaveLoadTestSuite, shouldntSaveFile_FileIsntOpen)
{
    EXPECT_CALL(fileMock, isOpen()).WillOnce(Return(false));

    QASaver saver(fileMock, fileSerializerFactoryMock);
    EXPECT_THROW(saver.save(QA(Question("question"), Answer("answer"))), FileException);
}

TEST_F(QASaveLoadTestSuite, shouldntSaveFile_FileIsntWriteable)
{
    EXPECT_CALL(fileMock, isOpen()).WillOnce(Return(true));
    EXPECT_CALL(fileMock, isWritable()).WillOnce(Return(false));


    QASaver saver(fileMock, fileSerializerFactoryMock);
    EXPECT_THROW(saver.save(QA(Question("question"), Answer("answer"))), FileException);
}
