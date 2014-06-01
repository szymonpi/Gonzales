#pragma once

#include "../../GonzalesApp/qa/QAsSelection/IQAsToLearnCheckedByUserProvider.h"
#include "../gmock.h"

class QAsToLearnCheckedByUserProviderMock: public IQAsToLearnCheckedByUserProvider
{
public:
    MOCK_METHOD0(getQAs, std::vector<std::shared_ptr<QA>>());
};
