#pragma once
#include "IQAsSelector.h"
#include "../../QAToViewConverter.h"

class isNotLearned
{
public:

    bool operator()(std::shared_ptr<QA> qa)
    {
        if(!qa->hasHistory())
            return false;
        if(!qa->isLearned())
            return true;
        return false;
    }

};
