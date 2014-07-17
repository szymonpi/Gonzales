#pragma once
#include "../../GonzalesApp/qa/qaio/IQAsFilePathProvider.h"
#include "../gmock.h"


class QAsFilePathProviderMock : public IQAsFilePathProvider
{
public:
    MOCK_CONST_METHOD0(getPath, QString());
};
