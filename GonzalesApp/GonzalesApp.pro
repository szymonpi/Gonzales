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
    teaching/teacher.cpp \
    user/logindialog.cpp \
    user/dialogcreateaccount.cpp \
    user/accountcreator.cpp \
    user/accountsprovider.cpp \
    qa/qarepository.cpp \
    user/authorizer.cpp \
    user/credentialsvalidator.cpp

HEADERS  += mainwindow.h \
    qa/question.h \
    qa/qasaver.h \
    qa/qaloader.h \
    qa/qaimporter.h \
    qa/qacontainer.h \
    qa/answer.h \
    teaching/teacher.h \
    teaching/teacheradapter.h \
    common/common.h \
    user/logindialog.h \
    user/dialogcreateaccount.h \
    user/accountcreator.h \
    common/applicationsettings.h \
    user/accountsprovider.h \
    common/qtproxies/readablewritablefile.h \
    common/qtproxies/fileserializerfactory.h \
    common/qtproxies/fileserializer.h \
    common/qtproxies/filefactory.h \
    common/qtproxies/filedeserializerfactory.h \
    common/qtproxies/filedeserializer.h \
    common/qtproxies/file.h \
    common/qtproxies/applicationsettings.h \
    teaching/iteacher.h \
    qa/qarepository.h \
    qa/iqarepository.h \
    user/authorizer.h \
    user/credentialsvalidator.h

FORMS    += mainwindow.ui \
    user/logindialog.ui \
    user/dialogcreateaccount.ui
