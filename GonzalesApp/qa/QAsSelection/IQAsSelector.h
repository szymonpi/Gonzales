#pragma once

#include <QVector>
#include "../QA.h"
#include <memory>

class IQAsSelector
{
public:
    virtual ~IQAsSelector(){}
    virtual QVector<std::shared_ptr<QA>> select(QVector<std::shared_ptr<QA>> qas) = 0;
};
