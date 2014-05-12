#include <iostream>
#include <memory>

#include "../gtest.h"
#include "../gmock.h"

#include <QQueue>
#include "../../GonzalesApp/qa/qaimporter.h"
#include "FileMock.h"

using namespace testing;

class QATextFileImporterTestSuite : public testing::Test
{
protected:
    QATextFileImporterTestSuite():
        filePath("path"),
        m_fileMock(std::make_shared<FileMock>()),
        m_fileFacotryMock(std::make_shared<FileFactoryMock>()),
        importer(m_fileFacotryMock)
    {

    }

    void SetUp()
    {
        EXPECT_CALL(*m_fileFacotryMock, create(filePath)).WillOnce(Return(m_fileMock));
    }

    void fileShouldOpen(bool open)
    {
        EXPECT_CALL(*m_fileMock, open(_)).WillOnce(Return(open));
    }

    QString filePath;
    std::shared_ptr<FileMock> m_fileMock;
    std::shared_ptr<FileFactoryMock> m_fileFacotryMock;
    QAFromTextFileImporter importer;
};

TEST_F(QATextFileImporterTestSuite, fileShouldThrowCantOpenFile)
{
    fileShouldOpen(false);
    EXPECT_THROW(importer.import(filePath), FileException);
}

TEST_F(QATextFileImporterTestSuite, shouldntImportAnyQAFromEmptyFile)
{
    fileShouldOpen(true);
    EXPECT_CALL(*m_fileMock, readLine()).WillOnce(Return(QString()));
    EXPECT_THROW(importer.import(filePath), FileException);
}

TEST_F(QATextFileImporterTestSuite, shouldImportOneQA)
{
    fileShouldOpen(true);
    QString line = "question answer";
    EXPECT_CALL(*m_fileMock, readLine())
                                    .WillOnce(Return(line))
                                    .WillOnce(Return(QString("")));
    std::vector<std::shared_ptr<QA> > importedQas = importer.import(filePath);
    ASSERT_FALSE(importedQas.empty());
    std::shared_ptr<QA> importedQa = importedQas[0];
    EXPECT_EQ(Question("question"), importedQa->question);
    EXPECT_EQ(Answer("answer"), importedQa->answer);
}

TEST_F(QATextFileImporterTestSuite, shouldntImportImproperQA)
{
    fileShouldOpen(true);
    QString line = "question ";
    EXPECT_CALL(*m_fileMock, readLine())
                                    .WillOnce(Return(line))
                                    .WillOnce(Return(QString("")));
    EXPECT_THROW(importer.import(filePath), FileException);
}

TEST_F(QATextFileImporterTestSuite, shouldImportTwoQAs)
{
    fileShouldOpen(true);
    QString firstLine = "question answer";
    QString secondLine = "question answer";
    EXPECT_CALL(*m_fileMock, readLine())
                                    .WillOnce(Return(firstLine))
                                    .WillOnce(Return(QString(" ")))
                                    .WillOnce(Return(secondLine))
                                    .WillOnce(Return(QString("")));
    EXPECT_EQ(2, importer.import(filePath).size());
}

TEST_F(QATextFileImporterTestSuite, shouldImportOneQAsWithManyWhitespaces)
{
    fileShouldOpen(true);
    QString line = "     question             answer            ";
    EXPECT_CALL(*m_fileMock, readLine())
                                    .WillOnce(Return(line))
                                    .WillOnce(Return(QString("")));
    std::vector<std::shared_ptr<QA> > qAs = importer.import(filePath);
    ASSERT_TRUE(!qAs.empty());
    EXPECT_EQ(1, qAs.size());

    std::shared_ptr<QA> importedQA = qAs.front();

    EXPECT_EQ(Question("question"), importedQA->question);
    EXPECT_EQ(Answer("answer"), importedQA->answer);
}
