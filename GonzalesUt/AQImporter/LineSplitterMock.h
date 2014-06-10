#pragma once

#include "../gmock.h"
#include "../../GonzalesApp/qa/ILineSplitter.h"

class LineSplitterMock : public ILineSplitter
{
public:
    MOCK_METHOD1(splitLine, QStringList(const QString &line));
};
