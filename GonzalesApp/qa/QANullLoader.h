#pragma once

#include "../Common/SimpleTree/Node.h"
#include "IQALoader.h"

class QANullLoader: public IQALoader
{
public:
    SimpleTree::Node<QA> load(){ return SimpleTree::Node<QA>();}
};
