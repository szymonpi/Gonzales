#ifndef QALOADERMOCK_H
#define QALOADERMOCK_H

#include "../../GonzalesApp/qa/QALoader.h"
#include "../gmock.h"

class QALoaderMock: public IQALoader
{
public:
    MOCK_METHOD0(load, SimpleTree::Node<QA>());
};

#endif // QALOADERMOCK_H
