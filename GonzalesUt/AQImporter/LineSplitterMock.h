#pragma once

#include "../gmock.h"
#include "../../GonzalesApp/qa/qaio/ILineToImportSplitter.h"

class LineSplitterMock : public ILineToImportSplitter
{
public:
    MOCK_METHOD1(splitLine, QStringList(const QString &line));
};
