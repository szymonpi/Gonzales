#pragma once
#include "IQAmarker.h"
#include "IQARepository.h"

class QARepetitionMarker: public  IQAMarker
{
public:
    QARepetitionMarker(std::shared_ptr<IQARepository> repository):
        m_repository(repository)
    {}

    void markAsKnown(QA &qa) override
    {
        if(!wasMarkedAsUnknown)
        {
            auto today = QDate::currentDate();
            qa.repetitionsHistory.insert(today);
        }
        m_marker->markAsKnown(qa);
    }

    void eraseEntryFromRepetitionHistory(QA &qa)
    {
        auto todayEntry = qa.repetitionsHistory.find(QDate::currentDate());
        if(todayEntry != qa.repetitionsHistory.end())
            qa.repetitionsHistory.erase(todayEntry);
    }

    void markAsUnknown(QA &qa) override
    {
        wasMarkedAsUnknown = true;
        eraseEntryFromRepetitionHistory(qa);
        m_marker->markAsUnknown(qa);
    }
private:
    std::shared_ptr<IQARepository> m_repository;
    std::shared_ptr<IQAMarker> m_marker;
    bool wasMarkedAsUnknown;
};
