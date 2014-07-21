TEMPLATE = app

QT       += core gui

CONFIG += console
CONFIG -= app_bundle
CONFIG += qt
CONFIG += c++11
CONFIG += warn_off

SOURCES += \
    alltests.cpp \
    ../../GonzalesApp/user/AccountCreator.cpp \
    AccountCreatorTestSuite.cpp \
    accountsprovidetestsuite.cpp \
    QSettingsTestSuite.cpp \
    ../../GonzalesApp/user/CredentialsValidator.cpp \
    CredentialsValidatorTestSuite.cpp \
    AuthorizerTestSuite.cpp \
    ../../GonzalesApp/user/Authorizer.cpp

HEADERS += ../gtest.h \
        ../gmock.h \
    ../../GonzalesApp/user/AccountCreator.h \
    ../../GonzalesApp/user/AccountsProvider.h \
    ../../GonzalesApp/common/qtproxies/IApplicationSettings.h \
    ../../GonzalesApp/user/CredentialsValidator.h \
    ../../GonzalesApp/user/Authorizer.h \
    CredentialsValidatorMock.h \
    CredentialsValidatorFactoryMock.h \
    ApplicationSettingsMock.h

unix
{
    LIBS += -pthread
}
win32
{
    LIBPATH += C:/gtest/lib
    LIBPATH += C:/gmock/lib
}

LIBS += -lgtest
LIBS += -lgmock

