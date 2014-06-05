#pragma once

#include "../../GonzalesApp/qa/QAsSelection/QAsSelector.h"
#include "../gmock.h"

class QAsSelectorMock: public IQAsSelector
{
public:
    MOCK_METHOD1(select, std::vector<std::shared_ptr<QA>>(std::vector<std::shared_ptr<QA> > &));
};
