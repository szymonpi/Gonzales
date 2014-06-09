#pragma once
#include "IQAmarker.h"
#include "IQARepository.h"

class QAMarker: public  IQAMarker
{
public:
    QAMarker(std::shared_ptr<IQARepository> repository):
        m_repository(repository)
    {}

    void markAsKnown(QA &qa) override
    {
        qa.addHistoryEntry(QDateTime::currentDateTime(), QA::AnswerRating::Correct);
        m_repository->onQAsUpdate();
    }

    void markAsUnknown(QA &qa) override
    {
        qa.addHistoryEntry(QDateTime::currentDateTime(), QA::AnswerRating::Incorrect);
        m_repository->onQAsUpdate();
    }
private:
    std::shared_ptr<IQARepository> m_repository;
};
