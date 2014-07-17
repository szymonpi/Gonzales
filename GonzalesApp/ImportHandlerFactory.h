#ifndef IMPORTHANDLERFACTORY_H
#define IMPORTHANDLERFACTORY_H
#include "uiobservers/ExceptionHandler.h"
#include "uiobservers/FilePathByDialogSelector.h"
#include "qa/qaio/QAImporter.h"
#include "qa/qaio/QAsAppender.h"
#include "qa/ImportHandler.h"
#include "ui/dialogs/DialogQAImporterSelector.h"

class ImportHandlerFactory{
public:
    ImportHandlerFactory(std::shared_ptr<IQARepository> l_repository):
        m_repository(l_repository)
    {

    }

    std::shared_ptr<ImportHandler> create()
    {
        std::shared_ptr<IExceptionHandler> l_exceptionHandler = std::make_shared<ExceptionHandler>();
        return std::make_shared<ImportHandler>(std::make_shared<FilePathByDialogSelector>(),
                                              std::make_shared<QAFromTextFileImporter>(),
                                              std::make_shared<QAsAppender>(std::make_shared<QAsImporterSelector>(),
                                                                                    m_repository),
                                              l_exceptionHandler);
    }

    std::shared_ptr<IQARepository> m_repository;
};

#endif // IMPORTHANDLERFACTORY_H
