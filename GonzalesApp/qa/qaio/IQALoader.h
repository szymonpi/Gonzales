#pragma once

class IQALoader
{
public:
    virtual SimpleTree::Node<QA> load() = 0;
    ~IQALoader(){}
};
