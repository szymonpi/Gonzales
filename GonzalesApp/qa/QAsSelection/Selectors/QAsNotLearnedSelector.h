#pragma once
#include "IQAsSelector.h"
#include "../../QAToViewConverter.h"

class isNotLearned
{
public:

    bool operator()(std::shared_ptr<QA> qa)
    {
        if(qa->answersHistory.empty())
            return false;
        return (--qa->answersHistory.end())->second == QA::AnswerRating::Incorrect;
    }

};
