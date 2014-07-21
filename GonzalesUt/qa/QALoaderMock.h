#pragma once

#include "../../GonzalesApp/qa/qaio/QALoader.h"
#include "../gmock.h"

class QALoaderMock: public IQALoader
{
public:
    MOCK_METHOD0(load, SimpleTree::Node<QA>());
};
