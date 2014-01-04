TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG += qt
CONFIG += c++11
CONFIG += warn_off

HEADERS += ../gtest.h \
           ../gmock.h \
    FileMock.h \
    FileSerializeMock.h \
    FileSerializerFactoryMock.h \
    FileDeserializerMock.h \
    FileDeserializerFactoryMock.h \
    ../../GonzalesApp/file/iodevice.h \
    ../../GonzalesApp/file/fileserializerfactory.h \
    ../../GonzalesApp/file/fileserializer.h \
    ../../GonzalesApp/file/filefactory.h \
    ../../GonzalesApp/file/filedeserializerfactory.h \
    ../../GonzalesApp/file/filedeserializer.h \
    ../../GonzalesApp/file/file.h \
    ../../GonzalesApp/qa/question.h \
    ../../GonzalesApp/qa/qasaver.h \
    ../../GonzalesApp/qa/qaloader.h \
    ../../GonzalesApp/qa/qaimporter.h \
    ../../GonzalesApp/qa/qacontainer.h \
    ../../GonzalesApp/qa/answer.h

SOURCES += \
    QAImporterTestSuite.cpp \
    FileTestSuite.cpp \
    QALoaderTestSuite.cpp \
    QASaverTestSuite.cpp \
    ../../GonzalesApp/qa/qasaver.cpp \
    ../../GonzalesApp/qa/qaloader.cpp \
    ../../GonzalesApp/qa/qaimporter.cpp

LIBPATH += C:/gtest/lib
LIBPATH += C:/gmock/lib

LIBS += -lgtest
LIBS += -lgmock

OTHER_FILES += \
    toimport.txt \
    toImportWithOneEmpty.txt \
    fileToWrite.txt

