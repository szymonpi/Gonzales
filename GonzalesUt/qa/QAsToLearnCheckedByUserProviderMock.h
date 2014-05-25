#pragma once

#include "../../GonzalesApp/qa/IQAsToLearnCheckedByUserProvider.h"
#include "../gmock.h"

class QAsToLearnCheckedByUserProviderMock: public IQAsToLearnCheckedByUserProvider
{
public:
    MOCK_METHOD0(getQAs, QVector<std::shared_ptr<QA>>());
};
