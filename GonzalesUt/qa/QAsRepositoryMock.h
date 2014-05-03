#ifndef QASREPOSITORYMOCK_H
#define QASREPOSITORYMOCK_H
#include "../../GonzalesApp/qa/iqarepository.h"
#include "../gmock.h"

class QAsRepositoryMock: public IQARepository
{
public:
    MOCK_METHOD0(load, void());
    MOCK_METHOD0(onQAsUpdate, void());
    MOCK_METHOD0(getQAs, std::vector<SimpleTree::Node<QA> >&());
    MOCK_CONST_METHOD0(getQAs, const std::vector<SimpleTree::Node<QA> >&());
};
#endif // QASREPOSITORYMOCK_H
