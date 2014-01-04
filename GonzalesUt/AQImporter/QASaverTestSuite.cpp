#include <iostream>
#include <memory>

#include "../gtest.h"
#include "../gmock.h"

#include <QQueue>

#include "../../GonzalesApp/qa/qasaver.h"
#include "../../GonzalesApp/qa/qaloader.h"
#include "FileSerializeMock.h"
#include "FileSerializerFactoryMock.h"

#include "FileMock.h"

using namespace testing;

class QASaveTestSuite : public testing::Test
{
protected:
    QASaveTestSuite():
        fileMock(),
        fileSerializerMock(std::make_shared<FileSerializerMock>()),
        fileSerializerFactoryMock(std::make_shared<FileSerializerFactoryMock>()),
        saver(fileMock, fileSerializerFactoryMock),
        qa(Question("question"), Answer("answer"))
    {
    }

    void SetUp()
    {
        oneQAs.append(qa);

        twoQAs.append(qa);
        twoQAs.append(qa);
    }

    Matcher<const char *> questionMatcher(Question qa)
    {
        return Matcher<const char*>(StrEq(qa.getAsString()));
    }

    Matcher<const char *> answerMatcher(Answer qa)
    {
        return Matcher<const char*>(StrEq(qa.getAsString()));
    }

    Matcher<quint16> fileVersionMatcher(QAFileVersion fv)
    {
        return  Matcher<quint16>(static_cast<quint16>(QAFileVersion1));
    }

    void saveWillThrow()
    {
        EXPECT_THROW(saver.save(oneQAs), FileException);
    }

    void expectSerializeQaVersion()
    {
        EXPECT_CALL(*fileSerializerMock, serialize(fileVersionMatcher(QAFileVersion1)));
    }

    void expectSerializeQA(unsigned times = 1)
    {
        EXPECT_CALL(*fileSerializerMock, serialize(questionMatcher(qa.question))).Times(times);
        EXPECT_CALL(*fileSerializerMock, serialize(answerMatcher(qa.answer))).Times(times);
    }

    void expectDataStreamStatusOk()
    {
        EXPECT_CALL(*fileSerializerMock, status()).WillOnce(Return(QDataStream::Ok));
    }

    void expectFileIsReadyToWrite()
    {
        QFile file;
        EXPECT_CALL(*fileSerializerFactoryMock, create(_)).WillOnce(Return(fileSerializerMock));
        EXPECT_CALL(fileMock, getIODevice()).WillOnce(Return(&file));
        expectFileIsWritable(true);
    }

    void expectFileIsOpen(bool open)
    {
        EXPECT_CALL(fileMock, isOpen()).WillOnce(Return(open));
    }

    void expectFileIsWritable(bool writable)
    {
        expectFileIsOpen(true);
        EXPECT_CALL(fileMock, isWritable()).WillOnce(Return(writable));
    }



    FileMock fileMock;
    std::shared_ptr<FileSerializerMock> fileSerializerMock;
    std::shared_ptr<FileSerializerFactoryMock> fileSerializerFactoryMock;
    QASaver saver;
    QQueue<QA> oneQAs;
    QQueue<QA> twoQAs;
    QA qa;

};

TEST_F(QASaveTestSuite, shouldSaveOneQA)
{
    expectFileIsReadyToWrite();
    expectSerializeQaVersion();
    expectSerializeQA();
    expectDataStreamStatusOk();
    ASSERT_TRUE(saver.save(oneQAs));
}

TEST_F(QASaveTestSuite, shouldSaveTwoQA)
{
    expectFileIsReadyToWrite();
    expectSerializeQaVersion();
    expectSerializeQA(2);
    expectDataStreamStatusOk();
    ASSERT_TRUE(saver.save(twoQAs));
}

TEST_F(QASaveTestSuite, shouldntSaveFile_FileIsntOpen)
{
    expectFileIsOpen(false);
    saveWillThrow();
}

TEST_F(QASaveTestSuite, shouldntSaveFile_FileIsntWriteable)
{
    expectFileIsWritable(false);
    saveWillThrow();
}

