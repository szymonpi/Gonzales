#pragma once

#include "../../GonzalesApp/qa/QAToViewConverter.h"
#include "../gmock.h"

class QAToViewConverterMock: public QAToViewConverter
{
public:
    MOCK_CONST_METHOD1(convert, std::shared_ptr<QAView>(const std::shared_ptr<QA> &qaData));
};
