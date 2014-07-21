#include <memory>
#include "../gtest.h"
#include "../gmock.h"
#include "../../GonzalesApp/qa/qaio/LineToImportSplitter.h"
#include "../CommonUtUtilities/PrintTo.h"

using namespace testing;

class LineSplitterTestSuite: public testing::Test
{

};

TEST_F(LineSplitterTestSuite, GivenEmptyLine_ShouldThrow)
{
    LineToImportSplitter lineSplitter;
    QString line("");
    EXPECT_THROW(lineSplitter.splitLine(line), std::logic_error);
}

TEST_F(LineSplitterTestSuite, GivenProperLineWithDash_ShouldReturnProper2Lines)
{
    LineToImportSplitter lineSplitter;
    QString line("question-sdsd - dddd-answer");
    QStringList list = lineSplitter.splitLine(line);
    EXPECT_EQ(2, list.size());
    EXPECT_EQ(QString("question-sdsd"),list.at(0));
    EXPECT_EQ(QString("dddd-answer"),list.at(1));
}

TEST_F(LineSplitterTestSuite, GivenProperLineWithQA_ShouldReturnProper2Lines)
{
    LineToImportSplitter lineSplitter;
    QString line("Q: question A: answer");
    QStringList list = lineSplitter.splitLine(line);
    EXPECT_EQ(2, list.size());
    EXPECT_EQ(QString("question"),list.at(0));
    EXPECT_EQ(QString("answer"),list.at(1));
}


