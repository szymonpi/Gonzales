#pragma once
#include "QA.h"
#include <memory>


class IQAMarker
{
public:
    virtual ~IQAMarker(){}
    virtual void markAsKnown(QA &qa) = 0;
    virtual void markAsUnknown(QA &qa) = 0;
};
