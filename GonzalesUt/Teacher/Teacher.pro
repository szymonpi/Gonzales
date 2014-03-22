
TEMPLATE = app
CONFIG += console
CONFIG += c++11
CONFIG += qt

SOURCES += \
    ../../GonzalesApp/teaching/teacher.cpp \
    TeacherTestSuite.cpp

HEADERS += ../gtest.h \
        ../gmock.h \
    ../../GonzalesApp/IUIAdapters.h \
    ../../GonzalesApp/teaching/teacheradapter.h \
    ../../GonzalesApp/teaching/teacher.h \
    TextPresenterMock.h \
    QasProviderMock.h

LIBPATH += C:/gtest/lib
LIBPATH += C:/gmock/lib

LIBS += -lgtest
LIBS += -lgmock
