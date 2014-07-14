#-------------------------------------------------
#
# Project created by QtCreator 2014-02-19T11:06:38
#
#-------------------------------------------------

TEMPLATE = app
QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += console
CONFIG -= app_bundle
CONFIG += qt
CONFIG += c++11
CONFIG += warn_off

HEADERS += ../gtest.h \
           ../gmock.h \
    ../../GonzalesApp/qa/QASaver.h \
    ../../GonzalesApp/qa/QALoader.h \
    ../../GonzalesApp/qa/QAImporter.h \
    ../../GonzalesApp/common/IExceptionHandler.h \
    ../../GonzalesApp/qa/ImportHandler.h \
    ../../GonzalesApp/qa/QAsAppender.h \
    ../../GonzalesApp/qa/IQAsAppender.h \
    ../../GonzalesApp/uiobservers/QAsDestinationSelector.h \
    ../../GonzalesApp/common/SimpleTree/Utils.h \
    ../../GonzalesApp/common/SimpleTree/Node.h \
    ExceptionHandlerMock.h \
    QuestionsCollectionPresenterMock.h \
    FilePathSelectorMock.h \
    QAsImporterMock.h \
    QAsAppenderMock.h \
    QAsDestinationSelectorMock.h \
    QAsRepositoryMock.h \
    QALoaderMock.h \
    QAsProviderMock.h \
    QAsToLearnCheckedByUserProviderMock.h \
    QASaverMock.h \
    ../../GonzalesApp/qa/QAsSelection/QAsToLearnProvider.h \
    ../../GonzalesApp/qa/QAsSelection/QAsToLearnCheckedByUserProvider.h \
    ../../GonzalesApp/qa/QAsSelection/QAsToLearnByUserChecker.h \
    ../../GonzalesApp/qa/QAsSelection/QAsProvider.h \
    ../../GonzalesApp/qa/QAsSelection/IQAsToLearnProvider.h \
    ../../GonzalesApp/qa/QAsSelection/IQAsToLearnCheckedByUserProvider.h \
    ../../GonzalesApp/qa/QAsSelection/Selectors/IQAsSelector.h \
    QAsSelectorMock.h \
    ../../GonzalesApp/qa/QAMarker.h \
    ../../GonzalesApp/qa/QALearnedChecker.h \
    ../../GonzalesApp/qa/QAsSelection/Selectors/Utils/QARepeatPeriodChecker.h \
    ../../GonzalesApp/qa/QAsSelection/Selectors/IQAsSelector.h \
    QAToViewConverterMock.h

SOURCES += \
    AllTests.cpp \
    QARepositoryTestSuite.cpp \
    ../../GonzalesApp/qa/QASaver.cpp \
    ../../GonzalesApp/qa/QALoader.cpp \
    ../../GonzalesApp/qa/QAImporter.cpp \
    ../../GonzalesApp/qa/QARepository.cpp \
    ../../GonzalesApp/qa/QAsAppender.cpp \
    ImportHandlertestSuite.cpp \
    FilePathSelectorTestSuite.cpp \
    QAsAppenderTestSuite.cpp \
    QAsToLearnProviderTestSuite.cpp \
    QAsToLearnByUserCheckerSuite.cpp \
    QAsToLearnCheckedByUserProviderTestSuite.cpp \
    ../../GonzalesApp/qa/QAsSelection/QAsToLearnProvider.cpp \
    ../../GonzalesApp/qa/QAsSelection/QAsToLearnCheckedByUserProvider.cpp \
    ../../GonzalesApp/qa/QAsSelection/QAsToLearnByUserChecker.cpp \
    ../../GonzalesApp/qa/QAsSelection/Selectors/QAsSelector.cpp \
    QAsSelectorTestSuite.cpp \
    QATestSuite.cpp \
    QAMarkerTestSuite.cpp \
    ../../GonzalesApp/qa/QAMarker.cpp \
    LineSplitterTestSuite.cpp \
    QALearnedCheckerTestSuite.cpp \
    ../../GonzalesApp/qa/QALearnedChecker.cpp \
    QAsForRepeatSelectorTestSuite.cpp \
    QARepeatPeriodCheckerTestSuite.cpp \
    ../../GonzalesApp/qa/QAsSelection/Selectors/Utils/QARepeatPeriodChecker.cpp

unix
{
    LIBS += -pthread
}
win32
{
    LIBPATH += C:/gtest/lib
    LIBPATH += C:/gmock/lib
}

LIBS += -lgtest
LIBS += -lgmock
