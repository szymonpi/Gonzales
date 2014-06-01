#pragma once
#include "../../common/SimpleTree/Node.h"
#include "../QA.h"

class QAsProvider
{
public:
    virtual const SimpleTree::Node<QA> &getQAs() const = 0;
    virtual SimpleTree::Node<QA> &getQAs() = 0;
    virtual ~QAsProvider(){}
};

