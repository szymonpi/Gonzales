#include <iostream>
#include <memory>

#include "../gtest.h"
#include "../gmock.h"

#include <QQueue>
#include "../../GonzalesApp/qa/qaio/QAImporter.h"
#include "FileMock.h"
#include "LineSplitterMock.h"

using namespace testing;

class QATextFileImporterTestSuite : public testing::Test
{
protected:
    QATextFileImporterTestSuite():
        filePath("path"),
        importer(m_lineSplitterMock, m_fileFacotryMock)
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
    std::shared_ptr<StrictMock<FileMock>> m_fileMock = std::make_shared<StrictMock<FileMock>>();
    std::shared_ptr<StrictMock<FileFactoryMock>> m_fileFacotryMock = std::make_shared<StrictMock<FileFactoryMock>>();
    std::shared_ptr<StrictMock<LineSplitterMock>> m_lineSplitterMock = std::make_shared<StrictMock<LineSplitterMock>>();
    QAFromTextFileImporter importer{m_lineSplitterMock, m_fileFacotryMock};
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
    QString line = "question - answer";
    EXPECT_CALL(*m_fileMock, readLine())
                                    .WillOnce(Return(line))
                                    .WillOnce(Return(QString("")));
    EXPECT_CALL(*m_lineSplitterMock, splitLine(line)).WillOnce(Return(QStringList() << QString("question")
                                                                  << QString("answer")));
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
    EXPECT_CALL(*m_lineSplitterMock, splitLine(line)).WillOnce(Throw(std::logic_error{"error"}));
    EXPECT_THROW(importer.import(filePath), FileException);
}

TEST_F(QATextFileImporterTestSuite, shouldImportTwoQAs)
{
    fileShouldOpen(true);
    QString firstLine = "question answer";
    QString secondLine = "question2 answer2";
    EXPECT_CALL(*m_fileMock, readLine())
                                    .WillOnce(Return(firstLine))
                                    .WillOnce(Return(QString(" ")))
                                    .WillOnce(Return(secondLine))
                                    .WillOnce(Return(QString("")));

    EXPECT_CALL(*m_lineSplitterMock, splitLine(firstLine)).WillOnce(Return(QStringList() << QString("question") << QString("answer")));
    EXPECT_CALL(*m_lineSplitterMock, splitLine(QString(" "))).WillOnce(Throw(std::logic_error{"error"}));
    EXPECT_CALL(*m_lineSplitterMock, splitLine(secondLine)).WillOnce(Return(QStringList() << QString("question2") << QString("answer2")));

    EXPECT_EQ(2, importer.import(filePath).size());
}
