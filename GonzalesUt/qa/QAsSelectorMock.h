#pragma once

#include "../../GonzalesApp/qa/QAsSelection/Selectors/QAsSelector.h"
#include "../gmock.h"

class QAsSelectorMock: public IQAsSelector
{
public:
    MOCK_CONST_METHOD1(select, std::vector<std::shared_ptr<QAView>>(std::vector<std::shared_ptr<QA> > &));
};
