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
    ui/dialogs/DialogCreateAccount.cpp \
    uiobservers/QuestionPresenter.cpp \
    uiobservers/AnswerPresenter.cpp \
    uiobservers/questioncollectionpresenter.cpp \
    QARepositoryFactory.cpp \
    qa/QAsSelection/QAsToLearnProvider.cpp \
    qa/QAsSelection/QAsToLearnCheckedByUserProvider.cpp \
    qa/QAsSelection/QAsTolearnByUserChecker.cpp

HEADERS  += user/UserInfo.h \
    qa/QAFilePathSelector.h \
    qa/ImportHandler.h \
    qa/QASerializer.h \
    qa/QASaver.h \
    qa/QALoader.h \
    qa/QARepository.h \
    qa/QAImporter.h \
    qa/IQARepository.h \
    qa/Answer.h \
    qa/Question.h \
    common/qtproxies/ApplicationSettings.h \
    common/qtproxies/File.h \
    common/qtproxies/FileFactory.h \
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
    uiobservers/QAsDestinationSelector.h \
    uiobservers/IExceptionHandler.h \
    uiobservers/FilePathSelector.h \
    uiobservers/FilePathByDialogSelector.h \
    uiobservers/ExceptionHandler.h \
    ui/mainwindow.h \
    ui/dialogs/DialogQAImporterSelector.h \
    ui/dialogs/LoginDialog.h \
    ui/dialogs/DialogCreateAccount.h \
    uiobservers/QuestionPresenter.h \
    uiobservers/AnswerPresenter.h \
    uiobservers/IQuestionPresenter.h \
    uiobservers/IAnswerPresenter.h \
    uiobservers/QuestionCollectionPresenter.h \
    uiobservers/IQuestionCollectionPresenter.h \
    TeacherControllerFactory.h \
    ImportHandlerFactory.h \
    QARepositoryFactory.h \
    common/SimpleTree/NodeSerializer.h \
    common/SimpleTree/InfosSerializer.h \
    common/SimpleTree/IInfosSerializer.h \
    common/qtproxies/IDataDeserializer.h \
    common/qtproxies/DataDeserializer.h \
    common/qtproxies/DataDeserializerFactory.h \
    common/qtproxies/DataSerializerFactory.h \
    common/qtproxies/DataSerializer.h \
    common/qtproxies/IDataSerializer.h \
    qa/QA.h \
    qa/QAsFilePathProvider.h \
    qa/IQAsFilePathProvider.h \
    qa/IQASaver.h \
    qa/QANullLoader.h \
    qa/QAsSelection/QAsToLearnProvider.h \
    qa/QAsSelection/QAsToLearnCheckedByUserProvider.h \
    qa/QAsSelection/QAsToLearnByUserChecker.h \
    qa/QAsSelection/QAsProvider.h \
    qa/QAsSelection/IQAsToLearnProvider.h \
    qa/QAsSelection/IQAsToLearnCheckedByUserProvider.h

FORMS    += ui/dialogs/logindialog.ui \
    ui/dialogs/dialogcreateaccount.ui \
    ui/dialogs/dialogqaimporterselector.ui \
    ui/mainwindow.ui

RESOURCES += \
    icons.qrc
