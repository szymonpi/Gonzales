#ifndef QASTOLEARNPROVIDERMOCK_H
#define QASTOLEARNPROVIDERMOCK_H

#include "../gmock.h"
#include "../../GonzalesApp/qa/QAsToLearnProvider.h"

class QAsToLearnProviderMock: public IQAsToLearnProvider
{
public:
    MOCK_METHOD0(getQAs, QQueue<std::shared_ptr<QA>>());
};

#endif // QASTOLEARNPROVIDERMOCK_H
