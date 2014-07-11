
QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = GonzalesApp
TEMPLATE = app
CONFIG += c++11

SOURCES += $$files(common/*.cpp) \
           $$files(common/qtproxies/*.cpp) \
           $$files(common/SimpleTree/*.cpp) \
           $$files(teaching/*.cpp) \
           $$files(ui/*.cpp) \
           $$files(ui/dialogs/*.cpp) \
           $$files(uiobservers/*.cpp) \
           $$files(user/*.cpp) \
           $$files(qa/*.cpp) \
           $$files(qa/QAsSelection/*.cpp) \
           main.cpp \
           QARepositoryFactory.cpp \
           ui/dialogs/LoginDialog.h

HEADERS += $$files(common/*.h) \
           $$files(common/qtproxies/*.h) \
           $$files(common/SimpleTree/*.h) \
           $$files(teaching/*.h) \
           $$files(ui/*.h) \
           $$files(ui/dialogs/*.h) \
           $$files(uiobservers/*.h) \
           $$files(user/*.h) \
           $$files(qa/*.h) \
           $$files(qa/QAsSelection/*.h) \
           ImportHandlerFactory.h \
           QARepositoryFactory.h \
           TeacherControllerFactory.h \
           ui/dialogs/LoginDialog.cpp

FORMS    += ui/dialogs/logindialog.ui \
    ui/dialogs/dialogcreateaccount.ui \
    ui/dialogs/dialogqaimporterselector.ui \
    ui/mainwindow.ui

RESOURCES += \
    icons.qrc
