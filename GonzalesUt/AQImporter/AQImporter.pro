TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG += qt
CONFIG += c++11
CONFIG += warn_off

HEADERS += ../gtest.h \
           ../gmock.h \
    ../../GonzalesApp/qaimporter.h \
    ../../GonzalesApp/fileoperations/fileserializer.h \
    ../../GonzalesApp/fileoperations/fileserializerfactory.h \
    ../../GonzalesApp/fileoperations/filedeserializer.h \
    ../../GonzalesApp/fileoperations/filedeserializerfactory.h \
    ../../GonzalesApp/fileoperations/file.h \
    ../../GonzalesApp/fileoperations/filefactory.h \
    FileMock.h \
    FileSerializeMock.h \
    FileSerializerFactoryMock.h \
    FileDeserializerMock.h \
    FileDeserializerFactoryMock.h \
    ../../GonzalesApp/qasaver.h \
    ../../GonzalesApp/qaloader.h

SOURCES += \
    ../../GonzalesApp/qaimporter.cpp \
    QAImporterTestSuite.cpp \
    FileTestSuite.cpp \
    ../../GonzalesApp/qasaver.cpp \
    ../../GonzalesApp/qaloader.cpp \
    QALoaderTestSuite.cpp \
    QASaverTestSuite.cpp

LIBPATH += C:/gtest/lib
LIBPATH += C:/gmock/lib

LIBS += -lgtest
LIBS += -lgmock

OTHER_FILES += \
    toimport.txt \
    toImportWithOneEmpty.txt \
    fileToWrite.txt

