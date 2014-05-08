#ifndef QASREPOSITORYMOCK_H
#define QASREPOSITORYMOCK_H
#include "../../GonzalesApp/qa/IQARepository.h"
#include "../gmock.h"

class QAsRepositoryMock: public IQARepository
{
public:
    MOCK_METHOD0(load, void());
    MOCK_METHOD0(onQAsUpdate, void());
    MOCK_METHOD0(getQAs, SimpleTree::Node<QA> &());
    MOCK_CONST_METHOD0(getQAs, SimpleTree::Node<QA>&());
};
#endif // QASREPOSITORYMOCK_H
