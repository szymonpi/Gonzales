#pragma once
#include "IQALearnedChecker.h"
#include "QA.h"
class QALearnedChecker: public IQALearnedChecker
{
public:
    bool isLearned(const QA &qa) override
    {
        auto aH = qa.getAnswersHistory();
        if(aH.empty())
            return false;
        auto lastItem = --aH.end();
        if(lastItem->second == QA::AnswerRating::Incorrect)
            return false;
        return true;
    }
};
