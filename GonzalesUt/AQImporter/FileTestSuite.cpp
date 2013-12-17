#include <iostream>
#include "../gtest.h"

#include <QQueue>
#include <QStringList>

#include "FileMock.h"

using namespace testing;

class FileTestSuite : public testing::Test
{
protected:
    void SetUp()
    {
        ExistingFile.setFileName("C:/projects/Gonzales/GonzalesUt/AQImporter/toimport.txt");
        NotExistingFile.setFileName("WrongFileName.txt");
    }


    File ExistingFile;
    File NotExistingFile;
};

TEST_F(FileTestSuite, testFileOpen)
{
    ASSERT_TRUE(ExistingFile.open(QFile::ReadOnly));
}

TEST_F(FileTestSuite, testCantOpenFile)
{
    ASSERT_FALSE(NotExistingFile.open(QFile::ReadOnly));
}

TEST_F(FileTestSuite, readOneLineFromFile)
{
    ExistingFile.open(QFile::ReadOnly);

    QString line = ExistingFile.readLine();
    EXPECT_TRUE(!line.isEmpty());
}

TEST_F(FileTestSuite, readTwoLineFromFile)
{
    ExistingFile.open(QFile::ReadOnly);

    QString currentLine = ExistingFile.readLine();
    QStringList lines;

    while(!currentLine.isEmpty())
    {
        lines.append(currentLine);
        currentLine = ExistingFile.readLine();
    };

    EXPECT_EQ(2, lines.size());
}
