TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG += qt
CONFIG += c++11
CONFIG += warn_off

HEADERS += ../gtest.h \
        ../gmock.h \
    ../../GonzalesApp/qaimporter.h \
    FileMock.h \
    ../../GonzalesApp/fileserializer.h \
    FileSerializeMock.h

SOURCES += \
    ../../GonzalesApp/qaimporter.cpp \
    QAImporterTestSuite.cpp \
    FileTestSuite.cpp \
    QASaveLoadTestSuite.cpp \
    ../../GonzalesApp/qasaver.cpp

LIBPATH += C:/gtest/lib
LIBPATH += C:/gmock/lib

LIBS += -lgtest
LIBS += -lgmock

OTHER_FILES += \
    toimport.txt \
    toImportWithOneEmpty.txt \
    fileToWrite.txt

