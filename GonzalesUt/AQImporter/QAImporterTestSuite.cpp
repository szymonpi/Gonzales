#include <iostream>
#include <memory>

#include "../gtest.h"
#include "../gmock.h"

#include <QQueue>

#include "../../GonzalesApp/qaimporter.h"
#include "FileMock.h"

using namespace testing;

class QAImporterTestSuite : public testing::Test
{
protected:
    QAImporterTestSuite():
        fileMock(),
        importer(std::make_shared<QAImporter>(fileMock))
    {

    }

    void SetUp()
    {
        properLine = "question answer";
        improperLine = "  question";
    }

    void fileShouldOpen(bool open)
    {
        EXPECT_CALL(fileMock, open(_)).WillOnce(Return(open));
    }

    FileMock fileMock;
    std::shared_ptr<QAImporter> importer;

    QString properLine;
    QString improperLine;
};

TEST_F(QAImporterTestSuite, shouldThrowCantOpenFile)
{
    fileShouldOpen(false);
    EXPECT_THROW(importer->import(), FileException);
}

TEST_F(QAImporterTestSuite, shouldntImportAnyQAFromEmptyFile)
{
    fileShouldOpen(true);
    EXPECT_CALL(fileMock, readLine()).WillOnce(Return(QString()));
    QQueue<QA> qaQueue =  importer->import();
    EXPECT_EQ(0, qaQueue.size());
}

TEST_F(QAImporterTestSuite, shouldImportOneQA)
{
    fileShouldOpen(true);
    QString line = "question answer";
    EXPECT_CALL(fileMock, readLine())
                                    .WillOnce(Return(line))
                                    .WillOnce(Return(QString("")));
    QQueue<QA> importedQas = importer->import();
    QA importedQa = importedQas.takeFirst();
    EXPECT_EQ(Question("question"), importedQa.question);
    EXPECT_EQ(Answer("answer"), importedQa.answer);
}

TEST_F(QAImporterTestSuite, shouldntImportImproperQA)
{
    fileShouldOpen(true);
    QString line = "question ";
    EXPECT_CALL(fileMock, readLine())
                                    .WillOnce(Return(line))
                                    .WillOnce(Return(QString("")));
    EXPECT_TRUE(importer->import().empty());
}

TEST_F(QAImporterTestSuite, shouldImportTwoQAs)
{
    fileShouldOpen(true);
    QString firstLine = "question answer";
    QString secondLine = "question answer";
    EXPECT_CALL(fileMock, readLine())
                                    .WillOnce(Return(firstLine))
                                    .WillOnce(Return(QString(" ")))
                                    .WillOnce(Return(secondLine))
                                    .WillOnce(Return(QString("")));
    EXPECT_EQ(2, importer->import().size());
}

TEST_F(QAImporterTestSuite, shouldImportOneQAsWithManyWhitespaces)
{
    fileShouldOpen(true);
    QString line = "     question             answer            ";
    EXPECT_CALL(fileMock, readLine())
                                    .WillOnce(Return(line))
                                    .WillOnce(Return(QString("")));
    QQueue<QA> qAs = importer->import();
    ASSERT_TRUE(!qAs.empty());
    EXPECT_EQ(1, qAs.size());

    QA importedQA = qAs.takeFirst();

    EXPECT_EQ(Question("question"), importedQA.question);
    EXPECT_EQ(Answer("answer"), importedQA.answer);
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
