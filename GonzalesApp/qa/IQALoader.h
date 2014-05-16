#pragma once

class IQALoader
{
public:
    virtual SimpleTree::Node<QA> load(const QString &userName) = 0;
    ~IQALoader(){}
};
