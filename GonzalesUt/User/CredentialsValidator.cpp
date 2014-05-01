#include "../gtest.h"
#include "../../GonzalesApp/user/credentialsvalidator.h"
#include "applicationsettingsmock.h"
#include <QStringList>


using namespace testing;

class CredentialsValidatorTestSuite: public ::testing::Test
{
public:
    CredentialsValidatorTestSuite():
        emptyString(),
        tooShortLogin("lo"),
        tooLongLogin("logiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiin"),
        improperLogin("login   with  spaces"),
        properLogin("properLogin"),
        tooShortPassword("pa"),
        tooLongPassword("passssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssword"),
        improperPassword("impro per password"),
        properPassword("Password*8")
    {

    }

    CredentialsValidator validator;
    QString emptyString;
    //login
    QString tooShortLogin;
    QString tooLongLogin;
    QString improperLogin;
    QString properLogin;
    //password
    QString tooShortPassword;
    QString tooLongPassword;
    QString improperPassword;
    QString properPassword;
};

//TEST_F(CredentialsValidatorTestSuite, InvalidCredentials_EmptyLogIn_ShouldThrowLoginException)
//{
//    EXPECT_THROW(validator.validate(emptyString,emptyString,emptyString), LoginException);
//}

//TEST_F(CredentialsValidatorTestSuite, shouldntCreateAccount_LoginIsTooShort)
//{
//    EXPECT_THROW(validator.validate(tooShortLogin,emptyString,emptyString), LoginException);
//}

//TEST_F(CredentialsValidatorTestSuite, shouldntCreateAccount_LoginIsTooLong)
//{
//    EXPECT_THROW(validator.validate(tooLongLogin,emptyString,emptyString), LoginException);
//}

//TEST_F(CredentialsValidatorTestSuite, shouldntCreateAccount_LoginIsImproper)
//{
//    EXPECT_THROW(validator.validate(improperLogin,emptyString,emptyString), LoginException);
//}

//TEST_F(CredentialsValidatorTestSuite, shouldntCreateAccount_PasswordIsEmpty)
//{
//    EXPECT_THROW(validator.validate(properLogin,emptyString,emptyString), PasswordException);
//}

//TEST_F(CredentialsValidatorTestSuite, shouldntCreateAccount_PasswordIsTooShort)
//{
//    EXPECT_THROW(validator.validate(properLogin,tooShortPassword,emptyString), PasswordException);
//}

//TEST_F(CredentialsValidatorTestSuite, shouldntCreateAccount_PasswordIsTooLong)
//{
//    EXPECT_THROW(validator.validate(properLogin,tooLongPassword,emptyString), PasswordException);
//}

//TEST_F(CredentialsValidatorTestSuite, shouldntCreateAccount_PasswordIsImproper)
//{
//    EXPECT_THROW(validator.validate(properLogin,improperPassword,emptyString), PasswordException);
//}

//TEST_F(CredentialsValidatorTestSuite, shouldntCreateAccount_ConfirmedPasswordIsDifferent)
//{
//    EXPECT_THROW(validator.validate(properLogin,properPassword,emptyString), PasswordException);
//}

//TEST_F(CredentialsValidatorTestSuite, shouldCreateAccountCreateSettingsEntry)
//{
//    EXPECT_NO_THROW(validator.validate(properLogin, properPassword, properPassword));
//}

