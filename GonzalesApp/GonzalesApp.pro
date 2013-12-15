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
    teacher.cpp \
    qaimporter.cpp

HEADERS  += mainwindow.h \
    teacher.h \
    answer.h \
    question.h \
    CommonCode/optional.hpp \
    qacontainer.h \
    QtLayerCode/teacheradapter.h \
    qaimporter.h \
    file.h \
    common.h

FORMS    += mainwindow.ui
