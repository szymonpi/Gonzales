TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG += qt
CONFIG += c++11

SOURCES += \
    ../../GonzalesApp/teaching/teacher.cpp \
    TeacherTestSuite.cpp

HEADERS += ../gtest.h \
        ../gmock.h \
    ../../GonzalesApp/teaching/teacheradapter.h \
    ../../GonzalesApp/teaching/teacher.h

LIBPATH += C:/gtest/lib
LIBPATH += C:/gmock/lib

LIBS += -lgtest
LIBS += -lgmock
