
#include "../gtest.h"
#include "../../GonzalesApp/user/authorizer.h"
#include "applicationsettingsmock.h"

using namespace testing;

TEST(AuthorizerTestSuite, ImproperCredentialsGivenLogin_ShouldntAuthorize)
{
    std::shared_ptr<ApplicationSettingsMock> l_settings = std::make_shared<StrictMock<ApplicationSettingsMock> >();
    Authorizer authorizer(l_settings);
    EXPECT_CALL(*l_settings, beginGroup(QString("Users")));
    EXPECT_CALL(*l_settings, contains(QString("login/password"))).WillOnce(Return(false));
    EXPECT_FALSE(authorizer.authorize("login", "password").isAuthorized);
}

TEST(AuthorizerTestSuite, ImproperCredentialsGivenPassword_ShouldntAuthorize)
{
    std::shared_ptr<ApplicationSettingsMock> l_settings = std::make_shared<StrictMock<ApplicationSettingsMock> >();
    Authorizer authorizer(l_settings);
    EXPECT_CALL(*l_settings, beginGroup(QString("Users")));
    EXPECT_CALL(*l_settings, contains(QString("login/password"))).WillOnce(Return(true));
    EXPECT_CALL(*l_settings, value(QString("login/password"), QVariant(QString("")))).WillOnce(Return(QVariant(QString(""))));
    EXPECT_FALSE(authorizer.authorize(QString("login"), QString("password")).isAuthorized);
}

TEST(AuthorizerTestSuite, ProperCredentialsGiven_ShouldAuthorize)
{
    std::shared_ptr<ApplicationSettingsMock> l_settings = std::make_shared<StrictMock<ApplicationSettingsMock> >();
    Authorizer authorizer(l_settings);
    EXPECT_CALL(*l_settings, beginGroup(QString("Users")));
    EXPECT_CALL(*l_settings, contains(QString("login/password"))).WillOnce(Return(true));
    EXPECT_CALL(*l_settings, value(QString("login/password"), QVariant(QString("")))).WillOnce(Return(QVariant(QString("password"))));
    EXPECT_TRUE(authorizer.authorize(QString("login"), QString("password")).isAuthorized);
}

