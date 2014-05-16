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
        ui/mainwindow.cpp \
    qa/QASaver.cpp \
    qa/QARepository.cpp \
    qa/QAimporter.cpp \
    qa/QALoader.cpp \
    qa/QAsToLearnProvider.cpp \
    qa/QAsAppender.cpp \
    teaching/Teacher.cpp \
    teaching/TeacherController.cpp \
    user/AccountCreator.cpp \
    user/AccountsProvider.cpp \
    user/Authorizer.cpp \
    user/CredentialsValidator.cpp \
    uiobservers/UIAdapters.cpp \
    uiobservers/FilePathSelector.cpp \
    uiobservers/FilePathByDialogSelector.cpp \
    uiobservers/ExceptionHandler.cpp \
    ui/dialogs/DialogQAImporterSelector.cpp \
    ui/dialogs/LoginDialog.cpp \
    ui/dialogs/DialogCreateAccount.cpp

HEADERS  += user/UserInfo.h \
    qa/QAFilePathSelector.h \
    qa/ImportHandler.h \
    qa/QASerializer.h \
    qa/QASaver.h \
    qa/QAContainer.h \
    qa/QALoader.h \
    qa/QARepository.h \
    qa/QAImporter.h \
    qa/IQARepository.h \
    qa/QAsToLearnProvider.h \
    qa/Answer.h \
    qa/Question.h \
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
    user/ICredentialsValidator.h \
    qa/IQAsAppender.h \
    qa/QAsAppender.h \
    qa/IQAFilePathSelector.h \
    qa/IQALoader.h \
    qa/IQASerializer.h \
    qa/IQAsToLearnProvider.h \
    uiobservers/UIAdapters.h \
    uiobservers/QAsDestinationSelector.h \
    uiobservers/IUIAdapters.h \
    uiobservers/IExceptionHandler.h \
    uiobservers/FilePathSelector.h \
    uiobservers/FilePathByDialogSelector.h \
    uiobservers/ExceptionHandler.h \
    ui/mainwindow.h \
    ui/dialogs/DialogQAImporterSelector.h \
    ui/dialogs/LoginDialog.h \
    ui/dialogs/DialogCreateAccount.h

FORMS    += ui/dialogs/logindialog.ui \
    ui/dialogs/dialogcreateaccount.ui \
    ui/dialogs/dialogqaimporterselector.ui \
    ui/mainwindow.ui \
    ui/dialogs/dialogqaimporterselector.ui \

RESOURCES += \
    icons.qrc
