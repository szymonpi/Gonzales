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

    char buffer[10240];
    qint64 lineSize = ExistingFile.readLine(buffer, sizeof(buffer));
    EXPECT_TRUE(lineSize != -1);
}

TEST_F(FileTestSuite, readTwoLineFromFile)
{
    ExistingFile.open(QFile::ReadOnly);

    char buffer[10240];
    qint64 lineSize = ExistingFile.readLine(buffer, sizeof(buffer));
    QStringList lines;

    while(lineSize != -1)
    {
        lines.append(QString::fromLocal8Bit(buffer, sizeof(buffer)));
        lineSize = ExistingFile.readLine(buffer, sizeof(buffer));
    };

    EXPECT_EQ(2, lines.size());
}
