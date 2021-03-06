#pragma once

#include "../uiobservers/FilePathSelector.h"
#include "qaio/QAImporter.h"
#include "qaio/QAsAppender.h"
#include "../uiobservers/IExceptionHandler.h"
#include <memory>

class ImportHandler
{
public:
    ImportHandler(std::shared_ptr<FilePathSelector> filePathSelector,
                  std::shared_ptr<QAsImporter> importer,
                  std::shared_ptr<IQAsAppender> importedQAsAppender,
                  std::shared_ptr<IExceptionHandler> exceptionHandler):
        m_filePathSelector(filePathSelector),
        m_importer(importer),
        m_importedQAsAppender(importedQAsAppender),
        m_exceptionHandler(exceptionHandler)
    {

    }

    void import()
    {
        try
        {
            if(!m_filePathSelector->select())
                return;
            m_importedQAsAppender->append(getimportedQAs());
        }
        catch(std::logic_error &e)
        {
            m_exceptionHandler->handleException(e.what(), "Import error");
        }
        catch(FileException &e)
        {
            m_exceptionHandler->handleException(e.what(), "Import error");
        }
    }

private:
    std::vector<std::shared_ptr<QA> > getimportedQAs()
    {
        return m_importer->import(m_filePathSelector->getSelected());
    }

    std::shared_ptr<FilePathSelector> m_filePathSelector;
    std::shared_ptr<QAsImporter> m_importer;
    std::shared_ptr<IQAsAppender> m_importedQAsAppender;
    std::shared_ptr<IExceptionHandler> m_exceptionHandler;
};
