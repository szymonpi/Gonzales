#pragma once
#include <memory>
#include <QString>

class UserInfo;
class QTreeWidget;
class IExceptionHandler;
class IQALoader;
class IQARepository;
class IQAsFilePathProvider;

class QARepositoryFactory
{
public:
    std::shared_ptr<IQARepository> create(const UserInfo &userInfo);

};
