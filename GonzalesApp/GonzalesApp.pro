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
    teaching/teacher.cpp \
    user/logindialog.cpp \
    user/dialogcreateaccount.cpp \
    user/accountcreator.cpp \
    user/accountsprovider.cpp \
    user/authorizer.cpp \
    user/credentialsvalidator.cpp \
    UIAdapters.cpp \
    teaching/teachercontroller.cpp \
    exceptionhandler.cpp \
    filepathselector.cpp \
    dialogqaimporterselector.cpp \
    qa/QASaver.cpp \
    qa/QARepository.cpp \
    qa/QAimporter.cpp \
    qa/ImportedQAsAppender.cpp \
    qa/QALoader.cpp \
    qa/QAsToLearnProvider.cpp \
    FilePathByDialogSelector.cpp

HEADERS  += mainwindow.h \
    teaching/teacher.h \
    user/logindialog.h \
    user/dialogcreateaccount.h \
    user/accountcreator.h \
    user/accountsprovider.h \
    teaching/iteacher.h \
    user/authorizer.h \
    user/credentialsvalidator.h \
    user/credentialsvalidatorfactory.h \
    user/icredentialsvalidator.h \
    user/UserInfo.h \
    UIAdapters.h \
    IUIAdapters.h \
    teaching/teachercontroller.h \
    exceptionhandler.h \
    IExceptionHandler.h \
    filepathselector.h \
    qa/QAFilePathSelector.h \
    dialogqaimporterselector.h \
    qa/ImportHandler.h \
    qa/QAsAppender.h \
    QAsDestinationSelector.h \
    qa/QASerializer.h \
    qa/QASaver.h \
    qa/ImportedQAsAppender.h \
    qa/QAContainer.h \
    qa/QALoader.h \
    qa/QARepository.h \
    qa/QAImporter.h \
    qa/IQARepository.h \
    qa/QAsToLearnProvider.h \
    qa/Answer.h \
    qa/Question.h \
    FilePathByDialogSelector.h \
    common/qtproxies/ApplicationSettings.h \
    common/qtproxies/File.h \
    common/qtproxies/FileDeserializer.h \
    common/qtproxies/FileDeserializerFactory.h \
    common/qtproxies/FileFactory.h \
    common/qtproxies/FileSerializer.h \
    common/qtproxies/FileSerializerFactory.h \
    common/qtproxies/IApplicationSettings.h \
    common/qtproxies/IFile.h \
    common/SimpleTree/Node.h \
    common/SimpleTree/Utils.h \
    common/Common.h

FORMS    += mainwindow.ui \
    user/logindialog.ui \
    user/dialogcreateaccount.ui \
    dialogqaimporterselector.ui

RESOURCES += \
    icons.qrc
