#include "../gtest.h"
#include "../gmock.h"

using namespace testing;

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
