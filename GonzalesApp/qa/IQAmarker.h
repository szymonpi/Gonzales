#pragma once
#include "QA.h"
#include <memory>


class IQAMarker
{
public:
    ~IQAMarker(){}
    virtual void markAsKnown(QA &qa) = 0;
    virtual void markAsUnknown(QA &qa) = 0;
};
