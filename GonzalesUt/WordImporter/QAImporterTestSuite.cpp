#include <iostream>
#include "../gtest.h"



class WordImporterTestSuite : public testing::Test
{


};

TEST_F(WordImporterTestSuite, ShouldImportOneWordFromFile)
{
    WordImporter importer;
    importer.import("fileToImport.txt");
}




int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
