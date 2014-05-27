#pragma once
#include <memory>
#include <QString>
class QTreeWidget;
class IExceptionHandler;
class IQALoader;
class QARepository;
class IQAsFilePathProvider;

class QARepositoryFactory
{
public:

    QARepositoryFactory(QTreeWidget &widget,
                        std::shared_ptr<IQAsFilePathProvider> filePathProvider,
                        std::shared_ptr<IQALoader> loader);
    std::shared_ptr<QARepository> create();

private:
    QTreeWidget &m_widget;
    std::shared_ptr<IQAsFilePathProvider> m_qasFilePathProvider;
    std::shared_ptr<IQALoader> m_loader;
};
