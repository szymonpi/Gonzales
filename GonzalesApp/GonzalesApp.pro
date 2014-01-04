#-------------------------------------------------
#
# Project created by QtCreator 2013-11-30T07:03:25
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = GonzalesApp
TEMPLATE = app
CONFIG += c++11


SOURCES += main.cpp\
        mainwindow.cpp \
    qa/qasaver.cpp \
    qa/qaloader.cpp \
    qa/qaimporter.cpp \
    teaching/teacher.cpp

HEADERS  += mainwindow.h \
    file/iodevice.h \
    file/fileserializerfactory.h \
    file/fileserializer.h \
    file/filefactory.h \
    file/filedeserializerfactory.h \
    file/filedeserializer.h \
    file/file.h \
    qa/question.h \
    qa/qasaver.h \
    qa/qaloader.h \
    qa/qaimporter.h \
    qa/qacontainer.h \
    qa/answer.h \
    teaching/teacher.h \
    teaching/teacheradapter.h \
    common/common.h

FORMS    += mainwindow.ui
