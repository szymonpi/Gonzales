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
        QDate date = QDate::currentDate();
        QA::AnswerRating answerRating = QA::AnswerRating::Correct;
        auto answerHistory = qa.getAnswersHistory();
        if(answerHistory.find(date) != answerHistory.end())
            if(answerHistory[date] == QA::AnswerRating::Incorrect)
                answerRating = QA::AnswerRating::Incorrect;

        qa.addHistoryEntry(date, answerRating);
        m_repository->onQAsUpdate();
    }

    void markAsUnknown(QA &qa) override
    {
        QDate dateTime = QDate::currentDate();
        qa.addHistoryEntry(dateTime, QA::AnswerRating::Incorrect);
        m_repository->onQAsUpdate();
    }
private:
    std::shared_ptr<IQARepository> m_repository;
};
