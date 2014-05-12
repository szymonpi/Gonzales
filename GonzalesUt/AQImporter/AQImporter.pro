TEMPLATE = app

QT       += core gui

CONFIG += console
CONFIG -= app_bundle
CONFIG += qt
CONFIG += c++11
CONFIG += warn_off

HEADERS += ../gtest.h \
           ../gmock.h \
    FileMock.h \
    FileSerializerFactoryMock.h \
    FileDeserializerMock.h \
    FileDeserializerFactoryMock.h \
    ../../GonzalesApp/qa/question.h \
    ../../GonzalesApp/qa/qasaver.h \
    ../../GonzalesApp/qa/qaloader.h \
    ../../GonzalesApp/qa/qaimporter.h \
    ../../GonzalesApp/qa/qacontainer.h \
    ../../GonzalesApp/qa/answer.h \
    ../../GonzalesApp/common/qtproxies/IFile.h \
    ../../GonzalesApp/common/qtproxies/FileFerializerFactory.h \
    ../../GonzalesApp/common/qtproxies/FileSerializer.h \
    ../../GonzalesApp/common/qtproxies/FileFactory.h \
    ../../GonzalesApp/common/qtproxies/FiledeFerializerFactory.h \
    ../../GonzalesApp/common/qtproxies/FileDeserializer.h \
    ../../GonzalesApp/common/qtproxies/File.h \
    FileSerializerMock.h \
    ../../GonzalesApp/common/SimpleTree/Node.h \
    ../../GonzalesApp/common/SimpleTree/Utils.h \
    QASerializerMock.h \
    ../../GonzalesApp/common/FileException.h

SOURCES += \
    QAImporterTestSuite.cpp \
    FileTestSuite.cpp \
    QALoaderTestSuite.cpp \
    QASaverTestSuite.cpp \
    ../../GonzalesApp/qa/qasaver.cpp \
    ../../GonzalesApp/qa/qaloader.cpp \
    ../../GonzalesApp/qa/qaimporter.cpp \
    AllTests.cpp

LIBPATH += C:/gtest/lib
LIBPATH += C:/gmock/lib

LIBS += -lgtest
LIBS += -lgmock

OTHER_FILES += \
    toimport.txt \
    toImportWithOneEmpty.txt \
    fileToWrite.txt

