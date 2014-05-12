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
    UIAdapters.cpp \
    qa/QASaver.cpp \
    qa/QARepository.cpp \
    qa/QAimporter.cpp \
    qa/ImportedQAsAppender.cpp \
    qa/QALoader.cpp \
    qa/QAsToLearnProvider.cpp \
    FilePathByDialogSelector.cpp \
    teaching/Teacher.cpp \
    teaching/TeacherController.cpp \
    user/AccountCreator.cpp \
    user/AccountsProvider.cpp \
    user/Authorizer.cpp \
    user/CredentialsValidator.cpp \
    user/DialogCreateAccount.cpp \
    user/LoginDialog.cpp \
    DialogQAImporterSelector.cpp \
    ExceptionHandler.cpp \
    FilePathSelector.cpp

HEADERS  += mainwindow.h \
    user/UserInfo.h \
    UIAdapters.h \
    IUIAdapters.h \
    IExceptionHandler.h \
    qa/QAFilePathSelector.h \
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
    common/Common.h \
    teaching/ITeacher.h \
    teaching/Teacher.h \
    teaching/TeacherController.h \
    user/Accountcreator.h \
    user/AccountsProvider.h \
    user/Authorizer.h \
    user/CredentialsValidator.h \
    user/CredentialsValidatorFactory.h \
    user/DialogCreateAccount.h \
    user/ICredentialsValidator.h \
    user/LoginDialog.h \
    DialogQAImporterSelector.h \
    ExceptionHandler.h \
    FilePathSelector.h

FORMS    += mainwindow.ui \
    user/logindialog.ui \
    user/dialogcreateaccount.ui \
    dialogqaimporterselector.ui

RESOURCES += \
    icons.qrc
