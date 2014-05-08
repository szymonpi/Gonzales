#ifndef QALOADERMOCK_H
#define QALOADERMOCK_H

#include "../../GonzalesApp/qa/QALoader.h"
#include "../gmock.h"

class QALoaderMock: public IQALoader
{
public:
    MOCK_METHOD1(load, SimpleTree::Node<QA>(const QString &userName));
};

#endif // QALOADERMOCK_H
