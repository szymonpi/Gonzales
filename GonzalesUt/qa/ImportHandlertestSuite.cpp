#include <memory>
#include "../gtest.h"
#include "../gmock.h"
#include "ExceptionHandlerMock.h"
#include "FilePathSelectorMock.h"
#include "QAsAppenderMock.h"
#include "QAsImporterMock.h"
#include "../../GonzalesApp/qa/ImportHandler.h"

using namespace testing;

class ImportHandlerTestSuite: public testing::Test
{
protected:
    ImportHandlerTestSuite():
        selectorMock(std::make_shared<StrictMock<FilePathSelectorMock> >()),
        exceptionMock(std::make_shared<StrictMock<ExceptionHandlerMock> >()),
        appenderMock(std::make_shared<StrictMock<QAsAppenderMock> >()),
        importerMock(std::make_shared<StrictMock<QAsImporterMock> >()),
        importHandler(selectorMock, importerMock, appenderMock, exceptionMock),
        errorMessage("error"),
        errorTitle("Import error"),
        path("path")
    {}
    std::shared_ptr<FilePathSelectorMock> selectorMock;
    std::shared_ptr<ExceptionHandlerMock> exceptionMock;
    std::shared_ptr<QAsAppenderMock> appenderMock;
    std::shared_ptr<QAsImporterMock> importerMock;
    ImportHandler importHandler;
    QString errorMessage;
    QString errorTitle;
    QString path;
};

TEST_F(ImportHandlerTestSuite, selectWillReturnDecline)
{
    EXPECT_CALL(*selectorMock, select()).WillOnce(Return(false));
    importHandler.import();
}

TEST_F(ImportHandlerTestSuite, selectWillReturnProperPathLogicErrorThrowedFromImport)
{
    EXPECT_CALL(*selectorMock, select()).WillOnce(Return(true));
    EXPECT_CALL(*importerMock, import(path)).WillOnce(Throw(std::logic_error(errorMessage.toStdString())));
    EXPECT_CALL(*selectorMock, getSelected()).WillOnce(Return(path));
    EXPECT_CALL(*exceptionMock, handleException(errorMessage, errorTitle));
    importHandler.import();
}

TEST_F(ImportHandlerTestSuite, selectWillReturnProperPathFileErrorThrowedFromImport)
{
    EXPECT_CALL(*selectorMock, select()).WillOnce(Return(true));
    EXPECT_CALL(*importerMock, import(path)).WillOnce(Throw(FileException(errorMessage.toStdString())));
    EXPECT_CALL(*selectorMock, getSelected()).WillOnce(Return(path));
    EXPECT_CALL(*exceptionMock, handleException(errorMessage, errorTitle));
    importHandler.import();
}

TEST_F(ImportHandlerTestSuite, AppenderWillAppendQAsProperly)
{
    EXPECT_CALL(*selectorMock, select()).WillOnce(Return(true));

    std::vector<std::shared_ptr<QA> > qAs;
    EXPECT_CALL(*selectorMock, getSelected()).WillOnce(Return(path));
    EXPECT_CALL(*importerMock, import(path)).WillOnce(Return(qAs));
    EXPECT_CALL(*appenderMock, append(qAs));
    importHandler.import();
}
