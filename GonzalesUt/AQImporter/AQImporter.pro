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
    DataSerializerFactoryMock.h \
    DataDeserializerMock.h \
    DataDeserializerFactoryMock.h \
    ../../GonzalesApp/qa/Question.h \
    ../../GonzalesApp/qa/QASaver.h \
    ../../GonzalesApp/qa/QALoader.h \
    ../../GonzalesApp/qa/QAImporter.h \
    ../../GonzalesApp/qa/QA.h \
    ../../GonzalesApp/qa/Answer.h \
    ../../GonzalesApp/common/qtproxies/IFile.h \
    ../../GonzalesApp/common/qtproxies/FileFerializerFactory.h \
    ../../GonzalesApp/common/qtproxies/DataSerializer.h \
    ../../GonzalesApp/common/qtproxies/FileFactory.h \
    ../../GonzalesApp/common/qtproxies/FiledeFerializerFactory.h \
    ../../GonzalesApp/common/qtproxies/DataDeserializer.h \
    ../../GonzalesApp/common/qtproxies/File.h \
    DataSerializerMock.h \
    ../../GonzalesApp/common/SimpleTree/Node.h \
    ../../GonzalesApp/common/SimpleTree/Utils.h \
    QASerializerMock.h \
    ../../GonzalesApp/common/FileException.h \
    DataSerializerFactoryMock.h \
    DataSerializerMock.h \
    DataDeserializerFactoryMock.h \
    DataDeserializerMock.h \
    QAsFilePathProviderMock.h \
    LineSplitterMock.h \
    ../../GonzalesApp/qa/ILineSplitter.h

SOURCES += \
    QAImporterTestSuite.cpp \
    FileTestSuite.cpp \
    QALoaderTestSuite.cpp \
    QASaverTestSuite.cpp \
    ../../GonzalesApp/qa/QASaver.cpp \
    ../../GonzalesApp/qa/QALoader.cpp \
    ../../GonzalesApp/qa/QAImporter.cpp \
    AllTests.cpp

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

OTHER_FILES += \
    toimport.txt \
    toImportWithOneEmpty.txt \
    fileToWrite.txt

