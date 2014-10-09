#include <iostream>
#include <memory>

#include "../gtest.h"
#include "../gmock.h"

#include <QQueue>

#include "../../GonzalesApp/qa/qaio/QASaver.h"
#include "../../GonzalesApp/qa/qaio/QALoader.h"
#include "DataSerializerMock.h"
#include "DataSerializerFactoryMock.h"
#include "QANodeSerializerMock.h"
#include "../../GonzalesApp/common/SimpleTree/Node.h"
#include "QAsFilePathProviderMock.h"
#include "FileMock.h"

using namespace testing;

class QASaveTestSuite : public testing::Test
{
protected:
    QASaveTestSuite():
        m_filePathProviderMock(std::make_shared<QAsFilePathProviderMock>()),
        m_fileMock(std::make_shared<FileMock>()),
        m_fileFactoryMock(std::make_shared<FileFactoryMock>()),
        m_DataSerializerMock(std::make_shared<DataSerializerMock>()),
        m_DataSerializerFactoryMock(std::make_shared<DataSerializerFactoryMock>()),
        m_qaSerializerMock(std::make_shared<QANodeSerializerMock>()),
        m_saver(m_filePathProviderMock, m_fileFactoryMock, m_qaSerializerMock, m_DataSerializerFactoryMock)
    {
    }

    void SetUp()
    {
        m_oneQAs.emplaceNode(m_qa);

        m_path = "path";
        EXPECT_CALL(*m_fileFactoryMock, create(m_path)).WillOnce(Return(m_fileMock));
        EXPECT_CALL(*m_filePathProviderMock, getPath()).WillOnce(Return(m_path));
    }

    Matcher<quint16> fileVersionMatcher(QAFileVersion fv)
    {
        return  Matcher<quint16>(static_cast<quint16>(QAFileVersion1));
    }

    void saveWillThrow(SimpleTree::Node<QA> &qAs)
    {
        EXPECT_THROW(m_saver.save(qAs), FileException);
    }

    void expectSerializeQaVersion()
    {
        EXPECT_CALL(*m_DataSerializerMock, serialize(fileVersionMatcher(QAFileVersion1)));
    }

    void expectSerializeQA()
    {
        EXPECT_CALL(*m_qaSerializerMock, serialize(_,_));
    }

    void expectDataStreamStatusOk()
    {
        EXPECT_CALL(*m_DataSerializerMock, status()).WillOnce(Return(QDataStream::Ok));
    }

    void expectDataStreamStatusNotOk()
    {
        EXPECT_CALL(*m_DataSerializerMock, status()).WillOnce(Return(QDataStream::WriteFailed));
    }

    void expectFileIsReadyToWrite()
    {
        QFile file;
        EXPECT_CALL(*m_DataSerializerFactoryMock, create(_)).WillOnce(Return(m_DataSerializerMock));
        EXPECT_CALL(*m_fileMock, getIODevice()).WillOnce(Return(&file));
        expectFileIsOpen(true);
    }

    void expectFileIsOpen(bool open)
    {
        EXPECT_CALL(*m_fileMock, open(QFile::WriteOnly)).WillOnce(Return(open));
    }


    std::shared_ptr<QAsFilePathProviderMock> m_filePathProviderMock;
    std::shared_ptr<FileMock> m_fileMock;
    std::shared_ptr<FileFactoryMock> m_fileFactoryMock;
    std::shared_ptr<DataSerializerMock> m_DataSerializerMock;
    std::shared_ptr<DataSerializerFactoryMock> m_DataSerializerFactoryMock;
    std::shared_ptr<QANodeSerializerMock> m_qaSerializerMock = std::make_shared<QANodeSerializerMock>();
    QASaver m_saver;
    SimpleTree::Node<QA> m_oneQAs;
    std::shared_ptr<QA> m_qa = std::make_shared<QA>();
    QString m_path;
};

TEST_F(QASaveTestSuite, shouldSaveOneQA)
{
    expectFileIsReadyToWrite();
    expectSerializeQaVersion();
    expectSerializeQA();
    expectDataStreamStatusOk();
    ASSERT_NO_THROW(m_saver.save(m_oneQAs));
}

TEST_F(QASaveTestSuite, shouldSaveTwoQA)
{
    expectFileIsReadyToWrite();
    expectSerializeQaVersion();
    expectSerializeQA();
    expectDataStreamStatusOk();
    ASSERT_NO_THROW(m_saver.save(m_oneQAs));
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
    expectSerializeQA();
    expectDataStreamStatusNotOk();
    saveWillThrow(m_oneQAs);
}

