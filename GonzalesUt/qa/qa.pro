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
    ../../GonzalesApp/qa/qarepository.h \
    ../../GonzalesApp/qa/qasaver.h \
    ../../GonzalesApp/qa/qaloader.h \
    ../../GonzalesApp/qa/qaimporter.h \
    ExceptionHandlerMock.h \
    ../../GonzalesApp/IExceptionHandler.h \
    QuestionsCollectionPresenterMock.h \
    ../../GonzalesApp/qa/ImportHandler.h \
    FilePathSelectorMock.h \
    QAsImporterMock.h \
    QAsAppenderMock.h \
    ../../GonzalesApp/qa/QAsAppender.h \
    ../../GonzalesApp/qa/importedqasappender.h \
    QAsDestinationSelectorMock.h \
    ../../GonzalesApp/QAsDestinationSelector.h \
    QAsRepositoryMock.h \
    ../../GonzalesApp/common/SimpleTree/utils.h \
    ../../GonzalesApp/common/SimpleTree/node.h

SOURCES += \
    AllTests.cpp \
    QARepositoryTestSuite.cpp \
    ../../GonzalesApp/qa/qasaver.cpp \
    ../../GonzalesApp/qa/qaloader.cpp \
    ../../GonzalesApp/qa/qaimporter.cpp \
    ../../GonzalesApp/qa/qarepository.cpp \
    ImportHandlertestSuite.cpp \
    FilePathSelectorTestSuite.cpp \
    QAsAppenderTestSuite.cpp \
    ../../GonzalesApp/qa/importedqasappender.cpp

LIBPATH += C:/gtest/lib
LIBPATH += C:/gmock/lib

LIBS += -lgtest
LIBS += -lgmock

