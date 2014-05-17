#ifndef QASPROVIDERMOCK_H
#define QASPROVIDERMOCK_H
#include "../../GonzalesApp/qa/IQARepository.h"
#include "../gmock.h"

class QAsProviderMock: public QAsProvider
{
public:
    MOCK_METHOD0(getQAs, SimpleTree::Node<QA> &());
    MOCK_CONST_METHOD0(getQAs, SimpleTree::Node<QA>&());
};

#endif // QASPROVIDERMOCK_H
