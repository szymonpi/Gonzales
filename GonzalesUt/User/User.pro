TEMPLATE = app

QT       += core gui

CONFIG += console
CONFIG -= app_bundle
CONFIG += qt
CONFIG += c++11
CONFIG += warn_off

SOURCES += \
    alltests.cpp \
    ../../GonzalesApp/user/accountcreator.cpp \
    ../../GonzalesApp/user/accountsprovider.cpp \
    AccountCreatorTestSuite.cpp \
    accountsprovidetestsuite.cpp \
    QSettingsTestSuite.cpp \
    ../../GonzalesApp/user/credentialsvalidator.cpp \
    CredentialsValidatorTestSuite.cpp \
    AuthorizerTestSuite.cpp \
    ../../GonzalesApp/user/authorizer.cpp

HEADERS += ../gtest.h \
        ../gmock.h \
    ../../GonzalesApp/user/accountcreator.h \
    ../../GonzalesApp/user/accountsprovider.h \
    ../../GonzalesApp/common/qtproxies/IApplicationSettings.h \
    ../../GonzalesApp/user/credentialsvalidator.h \
    ../../GonzalesApp/user/authorizer.h \
    CredentialsValidatorMock.h \
    CredentialsValidatorFactoryMock.h \
    applicationsettingsmock.h

LIBPATH += C:/gtest/lib
LIBPATH += C:/gmock/lib

LIBS += -lgtest
LIBS += -lgmock

