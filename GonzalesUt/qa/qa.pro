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
    ../../GonzalesApp/qa/QASaver.h \
    ../../GonzalesApp/qa/QALoader.h \
    ../../GonzalesApp/qa/QAImporter.h \
    ../../GonzalesApp/IExceptionHandler.h \
    ../../GonzalesApp/qa/ImportHandler.h \
    ../../GonzalesApp/qa/QAsAppender.h \
    ../../GonzalesApp/qa/ImportedQAsAppender.h \
    ../../GonzalesApp/QAsDestinationSelector.h \
    ../../GonzalesApp/common/SimpleTree/utils.h \
    ../../GonzalesApp/common/SimpleTree/node.h \
    ExceptionHandlerMock.h \
    QuestionsCollectionPresenterMock.h \
    FilePathSelectorMock.h \
    QAsImporterMock.h \
    QAsAppenderMock.h \
    QAsDestinationSelectorMock.h \
    QAsRepositoryMock.h \
    QALoaderMock.h \
    ../../GonzalesApp/qa/QAsToLearnProvider.h

SOURCES += \
    AllTests.cpp \
    QARepositoryTestSuite.cpp \
    ../../GonzalesApp/qa/QASaver.cpp \
    ../../GonzalesApp/qa/QALoader.cpp \
    ../../GonzalesApp/qa/QAImporter.cpp \
    ../../GonzalesApp/qa/QARepository.cpp \
    ../../GonzalesApp/qa/ImportedQAsAppender.cpp \
    ImportHandlertestSuite.cpp \
    FilePathSelectorTestSuite.cpp \
    QAsAppenderTestSuite.cpp \
    QAsToLearnProviderTestSuite.cpp \
    ../../GonzalesApp/qa/QAsToLearnProvider.cpp

LIBPATH += C:/gtest/lib
LIBPATH += C:/gmock/lib

LIBS += -lgtest
LIBS += -lgmock

