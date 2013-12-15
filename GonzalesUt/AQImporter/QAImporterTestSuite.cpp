#include <iostream>
#include "../gtest.h"
#include "../gmock.h"

#include <QQueue>

#include "../../GonzalesApp/qaimporter.h"
#include "FileMock.h"

using namespace testing;

TEST(QAImporterTestSuite, shouldThrowCantOpenFile)
{
    FileMock fileMock;
    EXPECT_CALL(fileMock, open(_)).WillOnce(Return(false));

    QAImporter importer(fileMock);
    EXPECT_THROW(importer.import(), FileException);
}

TEST(QAImporterTestSuite, shouldntImportAnyQAFromEmptyFile)
{
    FileMock fileMock;
    EXPECT_CALL(fileMock, open(_)).WillOnce(Return(true));
    EXPECT_CALL(fileMock, readLine(_,_)).WillOnce(Return(-1));
    QAImporter importer(fileMock);
    QQueue<QA> qaQueue =  importer.import();
    EXPECT_EQ(0, qaQueue.size());
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
