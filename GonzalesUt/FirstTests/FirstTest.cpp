#include <iostream>
#include <../gtest.h>

class TestingTestSuite: public ::testing::Test
{
protected:
    TestingTestSuite(){}
    void SetUp();
    void TearDown();
};

void TestingTestSuite::SetUp()
{

}

void TestingTestSuite::TearDown()
{

}

TEST(Testing, passingTest)
{
    ASSERT_TRUE(true);
}

TEST(Testing, failingTest)
{
    ASSERT_TRUE(false);
}

int main(int argv, char **argc)
{
    ::testing::InitGoogleTest(&argv, argc);
    return RUN_ALL_TESTS();
}
