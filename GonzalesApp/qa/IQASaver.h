#pragma once

#include <memory>
#include "../Common/SimpleTree/Node.h"


class IQASaver
{
public:
    ~IQASaver(){}
    virtual void save(const SimpleTree::Node<QA> &QuestionAnswers) = 0;
};
