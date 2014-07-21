#pragma once

#include "../../GonzalesApp/qa/qaio/QAsAppender.h"
#include "../gmock.h"

class QAsAppenderMock: public IQAsAppender
{
public:
    MOCK_METHOD1(append, void(std::vector<std::shared_ptr<QA> > importedQAs));
};

