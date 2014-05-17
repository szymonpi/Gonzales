#-------------------------------------------------
#
# Project created by QtCreator 2014-02-19T11:06:38
#
#-------------------------------------------------

TEMPLATE = app
QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

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
    ../../GonzalesApp/qa/IQAsAppender.h \
    ../../GonzalesApp/QAsDestinationSelector.h \
    ../../GonzalesApp/common/SimpleTree/Utils.h \
    ../../GonzalesApp/common/SimpleTree/Node.h \
    ExceptionHandlerMock.h \
    QuestionsCollectionPresenterMock.h \
    FilePathSelectorMock.h \
    QAsImporterMock.h \
    QAsAppenderMock.h \
    QAsDestinationSelectorMock.h \
    QAsRepositoryMock.h \
    QALoaderMock.h \
    ../../GonzalesApp/qa/QAsToLearnProvider.h \
    ../../GonzalesApp/qa/QAsToLearnSelector.h \
    QAsProviderMock.h

SOURCES += \
    AllTests.cpp \
    QARepositoryTestSuite.cpp \
    ../../GonzalesApp/qa/QASaver.cpp \
    ../../GonzalesApp/qa/QALoader.cpp \
    ../../GonzalesApp/qa/QAImporter.cpp \
    ../../GonzalesApp/qa/QARepository.cpp \
    ../../GonzalesApp/qa/QAsAppender.cpp \
    ImportHandlertestSuite.cpp \
    FilePathSelectorTestSuite.cpp \
    QAsAppenderTestSuite.cpp \
    QAsToLearnProviderTestSuite.cpp \
    ../../GonzalesApp/qa/QAsToLearnProvider.cpp \
    ../../GonzalesApp/qa/QAsTolearnSelector.cpp \
    QAsToLearnSelectorTestSuite.cpp

LIBPATH += C:/gtest/lib
LIBPATH += C:/gmock/lib

LIBS += -lgtest
LIBS += -lgmock

