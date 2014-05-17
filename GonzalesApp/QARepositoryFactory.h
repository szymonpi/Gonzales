#pragma once
#include <memory>
#include <QString>
class QTreeWidget;
class IExceptionHandler;
class QARepository;

class QARepositoryFactory
{
public:

    QARepositoryFactory(QTreeWidget &widget,
                        const QString &userName);
    std::shared_ptr<QARepository> create();

private:
    QTreeWidget &m_widget;
    QString m_userName;
};
