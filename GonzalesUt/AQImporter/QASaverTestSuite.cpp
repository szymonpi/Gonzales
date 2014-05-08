#include <iostream>
#include <memory>

#include "../gtest.h"
#include "../gmock.h"

#include <QQueue>

#include "../../GonzalesApp/qa/qasaver.h"
#include "../../GonzalesApp/qa/qaloader.h"
#include "FileSerializerMock.h"
#include "FileSerializerFactoryMock.h"
#include "QASerializerMock.h"
#include "../../GonzalesApp/common/SimpleTree/node.h"

#include "FileMock.h"

using namespace testing;

class QASaveTestSuite : public testing::Test
{
protected:
    QASaveTestSuite():
        m_fileMock(std::make_shared<FileMock>()),
        m_fileFactoryMock(std::make_shared<FileFactoryMock>()),
        m_fileSerializerMock(std::make_shared<FileSerializerMock>()),
        m_fileSerializerFactoryMock(std::make_shared<FileSerializerFactoryMock>()),
        m_qaSerializerMock(std::make_shared<QASerializerMock>()),
        m_saver(m_fileFactoryMock, m_qaSerializerMock, m_fileSerializerFactoryMock)
    {
    }

    void SetUp()
    {
        m_oneQAs.emplaceNode(m_qa);

        m_twoQAs.emplaceNode(m_qa);
        m_twoQAs.emplaceNode(m_qa);
        m_path = "path";
        EXPECT_CALL(*m_fileFactoryMock, create(m_path)).WillOnce(Return(m_fileMock));
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

    void saveWillThrow(SimpleTree::Node<QA> &qAs)
    {
        EXPECT_THROW(m_saver.save(qAs, m_path), FileException);
    }

    void expectSerializeQaVersion()
    {
        EXPECT_CALL(*m_fileSerializerMock, serialize(fileVersionMatcher(QAFileVersion1)));
    }

    void expectSerializeQA(unsigned times = 1)
    {
        EXPECT_CALL(*m_qaSerializerMock, serialize(_,_)).Times(times);
    }

    void expectDataStreamStatusOk()
    {
        EXPECT_CALL(*m_fileSerializerMock, status()).WillOnce(Return(QDataStream::Ok));
    }

    void expectDataStreamStatusNotOk()
    {
        EXPECT_CALL(*m_fileSerializerMock, status()).WillOnce(Return(QDataStream::WriteFailed));
    }

    void expectFileIsReadyToWrite()
    {
        QFile file;
        EXPECT_CALL(*m_fileSerializerFactoryMock, create(_)).WillOnce(Return(m_fileSerializerMock));
        EXPECT_CALL(*m_fileMock, getIODevice()).WillOnce(Return(&file));
        expectFileIsOpen(true);
    }

    void expectFileIsOpen(bool open)
    {
        EXPECT_CALL(*m_fileMock, open(QFile::WriteOnly)).WillOnce(Return(open));
    }



    std::shared_ptr<FileMock> m_fileMock;
    std::shared_ptr<FileFactoryMock> m_fileFactoryMock;
    std::shared_ptr<FileSerializerMock> m_fileSerializerMock;
    std::shared_ptr<FileSerializerFactoryMock> m_fileSerializerFactoryMock;
    std::shared_ptr<QASerializerMock> m_qaSerializerMock = std::make_shared<QASerializerMock>();
    QASaver m_saver;
    SimpleTree::Node<QA> m_oneQAs;
    SimpleTree::Node<QA> m_twoQAs;
    std::shared_ptr<QA> m_qa = std::make_shared<QA>();
    QString m_path;
};

TEST_F(QASaveTestSuite, shouldSaveOneQA)
{
    expectFileIsReadyToWrite();
    expectSerializeQaVersion();
    expectSerializeQA();
    expectDataStreamStatusOk();
    ASSERT_NO_THROW(m_saver.save(m_oneQAs, m_path));
}

TEST_F(QASaveTestSuite, shouldSaveTwoQA)
{
    expectFileIsReadyToWrite();
    expectSerializeQaVersion();
    expectSerializeQA(2);
    expectDataStreamStatusOk();
    ASSERT_NO_THROW(m_saver.save(m_twoQAs, m_path));
}

TEST_F(QASaveTestSuite, shouldntSaveFile_FileIsntOpen)
{
    expectFileIsOpen(false);
    saveWillThrow(m_oneQAs);
}

TEST_F(QASaveTestSuite, shouldFileDontSave_DataStreamIsNotOk)
{
    expectFileIsReadyToWrite();
    expectSerializeQaVersion();
    expectSerializeQA(2);
    expectDataStreamStatusNotOk();
    saveWillThrow(m_twoQAs);
}

