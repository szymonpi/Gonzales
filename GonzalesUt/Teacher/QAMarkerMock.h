#pragma once

#include "../gmock.h"
#include "../../GonzalesApp/qa/IQAmarker.h"


class QAMarkerMock: public IQAMarker
{
public:
    MOCK_METHOD1(markAsKnown, void(QA &qa));
    MOCK_METHOD1(markAsUnknown, void(QA &qa));
};
