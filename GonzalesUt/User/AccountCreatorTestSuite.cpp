
#include <iostream>
#include <stdexcept>
#include <QString>
#include "../gtest.h"
#include "../../GonzalesApp/user/AccountCreator.h"
#include "applicationsettingsmock.h"


using namespace testing;

class AccountCreatorTestSuite: public ::testing::Test
{
protected:
    AccountCreatorTestSuite():
        settingsMock(std::make_shared<ApplicationSettingsMock>()),
        creator(settingsMock),
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

    std::shared_ptr<ApplicationSettingsMock> settingsMock;
    AccountCreator creator;
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

TEST_F(AccountCreatorTestSuite, shouldntCreateAccount_EmptyLogIn)
{
    EXPECT_THROW(creator.create(emptyString,emptyString,emptyString), LoginException);
}

TEST_F(AccountCreatorTestSuite, shouldntCreateAccount_LoginIsTooShort)
{
    EXPECT_THROW(creator.create(tooShortLogin,emptyString,emptyString), LoginException);
}

TEST_F(AccountCreatorTestSuite, shouldntCreateAccount_LoginIsTooLong)
{
    EXPECT_THROW(creator.create(tooLongLogin,emptyString,emptyString), LoginException);
}

TEST_F(AccountCreatorTestSuite, shouldntCreateAccount_LoginIsImproper)
{
    EXPECT_THROW(creator.create(improperLogin,emptyString,emptyString), LoginException);
}

TEST_F(AccountCreatorTestSuite, shouldntCreateAccount_PasswordIsEmpty)
{
    EXPECT_THROW(creator.create(properLogin,emptyString,emptyString), PasswordException);
}

TEST_F(AccountCreatorTestSuite, shouldntCreateAccount_PasswordIsTooShort)
{
    EXPECT_THROW(creator.create(properLogin,tooShortPassword,emptyString), PasswordException);
}

TEST_F(AccountCreatorTestSuite, shouldntCreateAccount_PasswordIsTooLong)
{
    EXPECT_THROW(creator.create(properLogin,tooLongPassword,emptyString), PasswordException);
}

TEST_F(AccountCreatorTestSuite, shouldntCreateAccount_PasswordIsImproper)
{
    EXPECT_THROW(creator.create(properLogin,improperPassword,emptyString), PasswordException);
}

TEST_F(AccountCreatorTestSuite, shouldntCreateAccount_ConfirmedPasswordIsDifferent)
{
    EXPECT_THROW(creator.create(properLogin,properPassword,emptyString), PasswordException);
}

TEST_F(AccountCreatorTestSuite, shouldCreateAccountCreateSettingsEntry)
{
    EXPECT_CALL(*settingsMock, contains(_)).WillOnce(Return(false));
    EXPECT_CALL(*settingsMock, setValue(_, QVariant(properLogin)));
    EXPECT_CALL(*settingsMock, setValue(_, QVariant(properPassword)));
    EXPECT_NO_THROW(creator.create(properLogin, properPassword, properPassword));
}

TEST_F(AccountCreatorTestSuite, shouldntCreateAccount_AccountAlreadyCreated)
{
    EXPECT_CALL(*settingsMock, contains(_)).WillOnce(Return(true));
    EXPECT_THROW(creator.create(properLogin, properPassword, properPassword), PasswordException);
}
