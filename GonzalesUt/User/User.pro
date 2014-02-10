TEMPLATE = app
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
    QSettingsTestSuite.cpp

HEADERS += ../gtest.h \
        ../gmock.h \
    ../../GonzalesApp/user/accountcreator.h \
    ../../GonzalesApp/user/accountsprovider.h \
    ../../GonzalesApp/common/qtproxies/applicationsettings.h

LIBPATH += C:/gtest/lib
LIBPATH += C:/gmock/lib

LIBS += -lgtest
LIBS += -lgmock

