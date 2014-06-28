#pragma once
#include "QASimpleView.h"
#include <memory>


class QAViewFactory
{
public:
    ~QAViewFactory(){}
    virtual std::shared_ptr<QAView> createQAView(const std::shared_ptr<QA> &qaData) const = 0;
};
