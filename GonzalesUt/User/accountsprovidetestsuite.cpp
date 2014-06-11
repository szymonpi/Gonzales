#include "../gtest.h"
#include "../../GonzalesApp/user/AccountsProvider.h"
#include "applicationsettingsmock.h"
#include <QStringList>


using namespace testing;

class AccountsProvideTestSuite: public ::testing::Test
{

};

TEST_F(AccountsProvideTestSuite, shouldntReturnAccounts_GetAccountsReturnNothing)
{
    std::shared_ptr<ApplicationSettingsMock> appSettingsMock  = std::make_shared<ApplicationSettingsMock>();
    AccountsProvider provider(appSettingsMock);
    EXPECT_CALL(*appSettingsMock, beginGroup(QString("Users")));
    EXPECT_CALL(*appSettingsMock, childGroups()).WillOnce(Return(QStringList()));
    EXPECT_TRUE(provider.getAccounts().isEmpty());
}

TEST_F(AccountsProvideTestSuite, shouldReturnAccounts_GetAccountsReturn5Entries)
{
    std::shared_ptr<ApplicationSettingsMock> appSettingsMock  = std::make_shared<ApplicationSettingsMock>();
    AccountsProvider provider(appSettingsMock);
    EXPECT_CALL(*appSettingsMock, beginGroup(QString("Users")));
    QStringList users;
    users << QString("waldek")
          << QString("waldek1")
          << QString("waldek2")
          << QString("waldek3")
          << QString("waldek4");
    EXPECT_CALL(*appSettingsMock, childGroups()).WillOnce(Return(users));
    EXPECT_EQ(5, provider.getAccounts().size());
}
