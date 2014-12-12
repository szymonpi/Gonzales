

#include "../gtest.h"
#include "../gmock.h"
#include <QtGlobal>
#include <QCryptographicHash>
#include "../../GonzalesApp/common/Encryptors.h"



TEST(PasswordEncryptorTestSuite, generateSalt)
{
    SaltGenerator generator{};
    EXPECT_EQ(53, generator.generate(53).size());
}



