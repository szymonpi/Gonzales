#-------------------------------------------------
#
# Project created by QtCreator 2014-02-19T11:06:38
#
#-------------------------------------------------

TEMPLATE = app

CONFIG += console
CONFIG -= app_bundle
CONFIG += qt
CONFIG += c++11
CONFIG += warn_off

HEADERS += ../gtest.h \
           ../gmock.h \
    ../../GonzalesApp/common/simpletree.h \
    ../AQImporter/FileSerializerMock.h \
    ../AQImporter/FileDeserializerMock.h \
    ../CommonUtUtilities/PrintTo.h \
    ../CommonUtUtilities/CommonMocks.h

SOURCES += main.cpp \
    ../../GonzalesApp/common/simpletree.cpp \
    SimpleTreeTestSuite.cpp \
    NodeDeserializationTestSuite.cpp \
    NodeSerializationTestSuite.cpp


LIBPATH += C:/gtest/lib
LIBPATH += C:/gmock/lib

LIBS += -lgtest
LIBS += -lgmock

