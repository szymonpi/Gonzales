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
    qa/LineSplitter.cpp\
    qa/QAImporter.cpp\
    qa/QALoader.cpp\
    qa/QAMarker.cpp\
    qa/QARepository.cpp\
    qa/QAsAppender.cpp\
    qa/QASaver.cpp\
    qa/QAsSelection/QAsSelector.cpp\
    qa/QAsSelection/QAsTolearnByUserChecker.cpp\
    qa/QAsSelection/QAsToLearnCheckedByUserProvider.cpp\
    qa/QAsSelection/QAsToLearnProvider.cpp\
    QARepositoryFactory.cpp\
    teaching/TeacherController.cpp\
    teaching/Teacher.cpp\
    ui/dialogs/DialogCreateAccount.cpp\
    ui/dialogs/DialogQAImporterSelector.cpp\
    ui/dialogs/LoginDialog.cpp\
    ui/mainwindow.cpp\
    uiobservers/AnswerPresenter.cpp\
    uiobservers/ExceptionHandler.cpp\
    uiobservers/FilePathByDialogSelector.cpp\
    uiobservers/FilePathSelector.cpp\
    uiobservers/QuestionCollectionPresenter.cpp\
    uiobservers/QuestionPresenter.cpp\
    uiobservers/UIAdapters.cpp\
    user/AccountCreator.cpp\
    user/AccountsProvider.cpp\
    user/Authorizer.cpp\
    user/CredentialsValidator.cpp


HEADERS  += common/qtproxies/ApplicationSettings.h\
    common/qtproxies/DataDeserializerFactory.h\
    common/qtproxies/DataDeserializer.h\
    common/qtproxies/DataSerializerFactory.h\
    common/qtproxies/DataSerializer.h\
    common/qtproxies/FileFactory.h\
    common/qtproxies/IApplicationSettings.h\
    common/qtproxies/IDataDeserializer.h\
    common/qtproxies/IDataSerializer.h\
    common/qtproxies/IFile.h\
    common/SimpleTree/IInfosSerializer.h\
    common/SimpleTree/InfosSerializer.h\
    common/SimpleTree/NodeSerializer.h\
    ImportHandlerFactory.h\
    qa/ILineSplitter.h\
    qa/ImportHandler.h\
    qa/IQAFilePathSelector.h\
    qa/IQALoader.h\
    qa/IQAmarker.h\
    qa/IQAsAppender.h\
    qa/IQASaver.h\
    qa/IQASerializer.h\
    qa/IQAsFilePathProvider.h\
    qa/LineSplitter.h\
    qa/QAFilePathSelector.h\
    qa/QA.h\
    qa/QAMarker.h\
    qa/QANullLoader.h\
    qa/QAsAppender.h\
    qa/QASaver.h\
    qa/QASerializer.h\
    qa/QAsFilePathProvider.h\
    qa/QAsSelection/IQAsSelector.h\
    qa/QAsSelection/IQAsToLearnCheckedByUserProvider.h\
    qa/QAsSelection/IQAsToLearnProvider.h\
    qa/QAsSelection/QAsProvider.h\
    qa/QAsSelection/QAsSelector.h\
    qa/QAsSelection/QAsToLearnByUserChecker.h\
    qa/QAsSelection/QAsToLearnCheckedByUserProvider.h\
    qa/QAsSelection/QAsToLearnProvider.h\
    QARepositoryFactory.h\
    teaching/ITeacher.h\
    teaching/TeacherControllerFactory.h\
    teaching/TeacherController.h\
    teaching/Teacher.h\
    ui/dialogs/DialogCreateAccount.h\
    ui/dialogs/DialogQAImporterSelector.h\
    ui/dialogs/LoginDialog.h\
    ui/mainwindow.h\
    uiobservers/AnswerPresenter.h\
    uiobservers/ExceptionHandler.h\
    uiobservers/FilePathByDialogSelector.h\
    uiobservers/FilePathSelector.h\
    uiobservers/IAnswerPresenter.h\
    uiobservers/IExceptionHandler.h\
    uiobservers/IQuestionCollectionPresenter.h\
    uiobservers/IQuestionPresenter.h\
    uiobservers/QAsDestinationSelector.h\
    uiobservers/QuestionCollectionPresenter.h\
    uiobservers/QuestionPresenter.h\
    user/Accountcreator.h\
    user/AccountCreator.h\
    user/CredentialsValidatorFactory.h \
    user/AccountsProvider.h \
    user/Authorizer.h \
    user/CredentialsValidator.h \
    user/ICredentialsValidator.h \
    user/UserInfo.h \
    qa/QAImporter.h \
    user/UserInfo.h

FORMS    += ui/dialogs/logindialog.ui \
    ui/dialogs/dialogcreateaccount.ui \
    ui/dialogs/dialogqaimporterselector.ui \
    ui/mainwindow.ui

RESOURCES += \
    icons.qrc
