#pragma once
#include "IQAmarker.h"

class QAMarker: public  IQAMarker
{
public:
    void markAsKnown(QA &qa) override
    {
        qa.addHistoryEntry(QDateTime::currentDateTime(), QA::AnswerRating::Correct);
    }

    void markAsUnknown(QA &qa) override
    {
        qa.addHistoryEntry(QDateTime::currentDateTime(), QA::AnswerRating::Incorrect);
    }
};
