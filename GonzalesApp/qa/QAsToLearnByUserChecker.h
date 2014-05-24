#pragma once
#include <QTreeWidget>
#include "IQARepository.h"

class QAsToLearnByUserChecker
{
public:
    QAsToLearnByUserChecker(std::shared_ptr<IQARepository> qAsProvider);

    void select(const QTreeWidgetItem &item);

private:
    bool ItsSubject(const QTreeWidgetItem &item) const;

    std::shared_ptr<IQARepository> m_qARepository;
};

