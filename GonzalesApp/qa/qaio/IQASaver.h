#pragma once

#include <memory>
#include "../../common/SimpleTree/Node.h"


class IQASaver
{
public:
    virtual ~IQASaver(){}
    virtual void save(const SimpleTree::Node<QA> &QuestionAnswers) = 0;
};
