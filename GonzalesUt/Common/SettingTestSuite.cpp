#include "../gtest.h"
#include "../gmock.h"
#include "../../GonzalesApp/common/Setting.h"
#include "../User/applicationsettingsmock.h"


using namespace testing;

class IDummy
{
public:
    virtual int get() const = 0;
    virtual void setUi(const int&) = 0;
    virtual void setInUser(const int &) = 0;
};

class DummyMock: public IDummy
{
    public:
    MOCK_CONST_METHOD0(get, int());
    MOCK_METHOD1(setUi, void(const int&));
    MOCK_METHOD1(setInUser, void(const int&));
};



class SettingTestSuite: public testing::Test
{
public:
    std::shared_ptr<StrictMock<DummyMock>> mockHelper = std::make_shared<StrictMock<DummyMock>>();
    std::shared_ptr<StrictMock<ApplicationSettingsMock>> applicationSettingsMock =
            std::make_shared<StrictMock<ApplicationSettingsMock>>();
    const QString expectedName = "name";
    const QString expectedSettingsPath = "path";
    const int expectedVal = 1;
    const int defaultValue = 99;

    Setting<int> setting{[this](){ return this->mockHelper->get();},
                         [this](const int& val){ this->mockHelper->setUi(val); },
                         [this](const int& val){ this->mockHelper->setInUser(val); },
                         applicationSettingsMock,
                         expectedSettingsPath,
                         expectedName,
                         defaultValue};
};

TEST_F(SettingTestSuite, updateSettings)
{
    EXPECT_CALL(*mockHelper, get()).WillOnce(Return(expectedVal));
    EXPECT_CALL(*mockHelper, setInUser(expectedVal));
    EXPECT_CALL(*applicationSettingsMock, setValue(expectedSettingsPath+"/"+expectedName,
                                                   QVariant{expectedVal}));

    setting.update();
}

TEST_F(SettingTestSuite, EmptyValueGiven_ShouldLoadDefaultSetting)
{
    EXPECT_CALL(*applicationSettingsMock, value(expectedSettingsPath+"/"+expectedName,
                                                QVariant{defaultValue})).WillOnce(Return(defaultValue));
    EXPECT_CALL(*mockHelper, setUi(defaultValue));
    EXPECT_CALL(*mockHelper, setInUser(defaultValue));

    setting.load();
}

TEST_F(SettingTestSuite, ShouldLoadSetting)
{
    EXPECT_CALL(*applicationSettingsMock, value(expectedSettingsPath+"/"+expectedName, QVariant{defaultValue}))
            .WillOnce(Return(QVariant{expectedVal}));
    EXPECT_CALL(*mockHelper, setUi(expectedVal));
    EXPECT_CALL(*mockHelper, setInUser(expectedVal));
    setting.load();
}
