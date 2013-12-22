#include <iostream>
#include <memory>

#include "../gtest.h"
#include "../gmock.h"

using namespace testing;

class LessonTestSuite : public testing::Test
{

};

TEST_F(LessonTestSuite, shouldThrowCantOpenFile)
{
//    Lesson lesson;
//    lesson.setTeacher(teacher);
//    lesson.importMaterial();
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
